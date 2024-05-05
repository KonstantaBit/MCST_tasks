#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int acstrcmp(const void *a, const void *b) {
  return strcmp(*(const char **)a, *(const char **)b);
}

int destrcmp(const void *a, const void *b) {
  return -strcmp(*(const char **)a, *(const char **)b);
}

int aclencmp(const void *a, const void *b) {
  return strlen(*(const char **)a) - strlen(*(const char **)b);
}

int delencmp(const void *a, const void *b) {
  return strlen(*(const char **)b) - strlen(*(const char **)a);
  ;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Некорректные данные\n");
    exit(EXIT_FAILURE);
  }

  FILE *file_in = NULL;
  FILE *file_out = NULL;

  file_in = fopen(argv[1], "r");

  if (file_in == NULL) {
    printf("Файл %s не существует\n", argv[1]);
    exit(1);
  }

  if (access(argv[2], F_OK) != 0) {
    file_out = fopen(argv[2], "w");
    fclose(file_out);
  }

  file_out = fopen(argv[2], "r");

  int lines = 0;
  int max_len = 0;
  int cur_len = 0;

  while (
      !feof(file_in)) { // Считаю, сколько строк в файле и самую длинную из них
    char ch = fgetc(file_in);
    if (ch == '\n') {
      lines += 1;
      max_len = max_len < cur_len ? cur_len : max_len;
      cur_len = 0;
    } else {
      cur_len += 1;
    }
  }

  printf("%i %i\n", lines, max_len);

  char **all = calloc(lines, sizeof(char *)); // Двумерный массив
  rewind(file_in); // Перевожу каретку в начало потока

  int cntr = 0;
  for (int i = 0; i < lines; ++i) {
    char *temp = calloc(max_len + 1, sizeof(char));
    fgets(temp, max_len, file_in);
    all[i] = temp;
  }

  switch (atoi(argv[3])) {
  case 1:
    qsort(all, lines, sizeof(char *), acstrcmp);
    break;
  case 2:
    qsort(all, lines, sizeof(char *), destrcmp);
    break;
  case 3:
    qsort(all, lines, sizeof(char *), aclencmp);
    break;
  case 4:
    qsort(all, lines, sizeof(char *), delencmp);
    break;
  default:
    printf("Такого типа сортировки не существует\n");
    exit(EXIT_FAILURE);
    break;
  }

  for (int i = 0; i < lines; ++i) {
    printf("%s", all[i]);
    fputs(all[i], file_out);
  }

  for (int i = 0; i < lines; ++i)
    free(all[i]);
  free(all);

  fclose(file_in);
  fclose(file_out);

  return EXIT_SUCCESS;
}
