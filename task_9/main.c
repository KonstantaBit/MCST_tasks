#include <stdio.h>
#include <stdlib.h>

int max_sum(int *array, size_t size);

int main(int argc, char *argv[]) {
  size_t size = 0;
  printf("Введите длину последовательности\n");
  scanf("%zu", &size);
  int *array = calloc(size, sizeof(int));
  printf("Введите числа последовательности через пробел\n");
  for (int i = 0; i < size; ++i) {
    int temp;
    scanf("%d", &temp);
    array[i] = temp;
  }
  printf("%d", max_sum(array, size));
  free(array);
  return EXIT_SUCCESS;
}

int max_sum(int *array, size_t size) {
  int max_sum = array[0];
  int current_sum = array[0];
  for (int i = 1; i < size; ++i) {
    current_sum =
        array[i] > current_sum + array[i] ? array[i] : current_sum + array[i];
    max_sum = max_sum > current_sum ? max_sum : current_sum;
  }
  return max_sum;
}
