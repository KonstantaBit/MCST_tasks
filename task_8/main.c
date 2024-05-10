#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int flag = 0, i0, j0;

int **a0;
int **b0;
int **c0;

void handle_sigint(int sig) {
  if (flag) {
    for (int i = 0; i < 1000; ++i) {
      free(a0[i]);
      free(b0[i]);
      free(c0[i]);
    }

    free(a0);
    free(b0);
    free(c0);
    exit(EXIT_FAILURE);
  }
  flag = 1;
  printf("%d, %d\n", i0, j0);
  return;
}

int main(int argc, char *argv[]) {
  int **a = calloc(1000, sizeof(int *));
  int **b = calloc(1000, sizeof(int *));
  int **c = calloc(1000, sizeof(int *));

  a0 = a;
  b0 = b;
  c0 = c;

  for (int i = 0; i < 1000; ++i) {
    a[i] = calloc(1000, sizeof(int));
    b[i] = calloc(1000, sizeof(int));
    c[i] = calloc(1000, sizeof(int));
    for (int j = 0; j < 1000; ++j) {
      a[i][j] = (int)rand() % 100;
      b[i][j] = (int)rand() % 100;
      c[i][j] = 0;
    }
  }

  for (i0 = 0; i0 < 1000; ++i0) {
    for (j0 = 0; j0 < 1000; ++j0) {
      for (int k = 0; k < 1000; ++k) {
        c[i0][j0] += a[i0][k] * b[k][j0];
      }
      signal(SIGINT, handle_sigint);
      sleep(1);
    }
  }

  for (int i = 0; i < 1000; ++i) {
    free(a[i]);
    free(b[i]);
    free(c[i]);
  }

  free(a);
  free(b);
  free(c);

  return EXIT_SUCCESS;
}
