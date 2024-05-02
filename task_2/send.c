#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *fifo = "/tmp/CHATFIFO";
  int fd;
  mkfifo(fifo, 0666);
  fd = open(fifo, O_WRONLY);
  while (1) {
    char temp[256];
    fgets(temp, 256, stdin);
    printf("%s\n", temp);
    if (!strncmp(temp, "stop", 4)) {
      break;
    }
    write(fd, temp, strlen(temp) + 1);
  }
  close(fd);
  return EXIT_SUCCESS;
}
