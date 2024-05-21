#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  int code;

  char *allowed[] = {"1c+\0", "2c+\0", "2c3\0", "4c\0", "8c\0", "16c\0"};
  char **data = calloc(argc, sizeof(char *));
  int data_end = 0;
  int m_c = 0;
  int c_c = 0;
  int s_c = 0;
  int t_c = 0;

  while (1) {
    static struct option long_options[] = {
        {"elbrus", required_argument, 0, 'e'}, {0, 0, 0, 0}};

    int option_index = 0;
    int flag = 0;

    code = getopt_long(argc, argv, "e:mcst", long_options, &option_index);

    if (code == -1)
      break;

    char *temp = calloc(16, sizeof(char));
    char *op = optarg;
    switch (code) {
    case 'e':
      for (int i = 0; i < 6; ++i) {
        if (strcmp(allowed[i], op) == 0) {
          flag = 1;
          char f[16] = "--elbrus=   ";
          for (int j = 0; j < strlen(allowed[i]); ++j) {
            f[j + 9] = allowed[i][j];
          }
          temp = f;
        }
      }
      if (!flag) {
        printf("Options are incorrect\n %s is invalid\n", optarg);
        exit(EXIT_FAILURE);
      }
      break;
    case 'm':
      if (!m_c) {
        temp = "m";
        m_c = 1;
      }
      break;
    case 'c':
      if (!c_c) {
        temp = "c";
        c_c = 1;
      }
      break;
    case 's':
      if (!s_c) {
        temp = "s";
        s_c = 1;
      }
      break;
    case 't':
      if (!t_c) {
        temp = "t";
        t_c = 1;
      }
      break;
    case '?':
      printf("Options are incorrect\n");
      /* getopt_long already printed an error message. */
      exit(EXIT_FAILURE);
    }
    data[data_end] = temp;
    data_end += 1;
  }

  printf("Options are correct: ");
  for (int i = 0; i < data_end; ++i) {
    printf("%s, ", data[i]);
    // free(data[i]);
  }

  if (optind < argc) {
    printf("non-options: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);
    putchar('\n');
  }
  free(data);
  return EXIT_SUCCESS;
}
