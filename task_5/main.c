#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <syscall.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Некорректные данные\n");
    exit(EXIT_FAILURE);
  }

  int code = syscall(SYS_open, argv[1], O_RDONLY);

  if (code == -1) {
    fprintf(stderr, "Ошибка во время системного вызова, errno = %d\n", errno);
    fprintf(
        stderr, "sys_errlist: %s\n",
        strerror(
            errno)); // sys_errlist устарел, рекомендуют использовать strerror()
    perror("Ошибка во время выполнения системного вызова\n");
  }
  return EXIT_SUCCESS;
}
