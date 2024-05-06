#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Invalid number of arguments. Expected 2, got %d", argc);
    exit(EXIT_FAILURE);
  }

  FILE *file_in = NULL;
  FILE *file_out0 = NULL;
  FILE *file_out1 = NULL;
  int status = 0;

  file_in = fopen(argv[1], "r");

  if (file_in == NULL) {
    printf("Failed to open file: %s", argv[1]);
    exit(EXIT_FAILURE);
  }

  pid_t prcs = fork();

  if (prcs < 0) {
    printf("Failed to fork\n");
    exit(EXIT_FAILURE);
  } else if (prcs == 0) {
    file_out0 = fopen("out0.txt", "w");
    while (!feof(file_in)) {
      char ch = fgetc(file_in);
      fputc(ch, file_out0);
    }

    fclose(file_out0);
    file_out0 = fopen("out0.txt", "r");

    printf("Child process:\n");
    while (!feof(file_out0))
      printf("%c", fgetc(file_out0));
    printf("\n");

    fclose(file_in);
    fclose(file_out0);
    exit(0);
  } else {
    wait(&status);
    rewind(file_in);
    file_out1 = fopen("out1.txt", "w");
    while (!feof(file_in)) {
      char ch = fgetc(file_in);
      fputc(ch, file_out1);
    }

    fclose(file_out1);
    file_out1 = fopen("out1.txt", "r");

    printf("Parent process:\n");
    while (!feof(file_out1))
      printf("%c", fgetc(file_out1));
    printf("\n");

    fclose(file_in);
    fclose(file_out1);
  }
  return EXIT_SUCCESS;
}
