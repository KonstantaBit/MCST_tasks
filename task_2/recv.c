#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char *fifo = "/tmp/CHATFIFO";
  int fd;
  fd = open(fifo, O_RDONLY);
  while (1) {
    char temp[256];
    read(fd, temp, 256);
    printf("%s\n", temp);
  }
  close(fd);
  return EXIT_SUCCESS;
}
