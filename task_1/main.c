#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct merge_sort_arg {
  int *up;
  int *down;
  unsigned int left;
  unsigned int right;
};

void *merge_sort(void *);

int main(int argc, char *argv[]) {
  size_t size;
  printf("Enter array length:\n");
  scanf("%zu", &size);
  printf("Enter numbers separated by spaces:\n");
  int *array = calloc(size, sizeof(int));
  for (int i = 0; i < size; ++i) {
    int temp;
    scanf("%d", &temp);
    array[i] = temp;
  }

  int *buff = calloc(size, sizeof(int));

  struct merge_sort_arg run = {array, buff, 0, size - 1};

  int *result = merge_sort((void *)&run);

  for (int i = 0; i < size; ++i) {
    printf("%i ", result[i]);
  }

  free(array);
  free(buff);

  return EXIT_SUCCESS;
}

void *merge_sort(void *arg) {
  struct merge_sort_arg darg = *(struct merge_sort_arg *)arg;
  int *up = darg.up;
  int *down = darg.down;
  unsigned int left = darg.left;
  unsigned int right = darg.right;

  if (left == right) {
    down[left] = up[left];
    return down;
  }

  unsigned int middle = left + (right - left) / 2;

  struct merge_sort_arg left_arg = {up, down, left, middle};
  struct merge_sort_arg right_arg = {up, down, middle + 1, right};

  pthread_t left_thread, right_thread;

  void *left_result;
  void *right_result;

  pthread_create(&left_thread, NULL, merge_sort, (void *)&left_arg);
  pthread_create(&right_thread, NULL, merge_sort, (void *)&right_arg);

  pthread_join(left_thread, &left_result);
  pthread_join(right_thread, &right_result);

  int *l_buff = (int *)left_result;
  int *r_buff = (int *)right_result;

  // слияние двух отсортированных половин
  int *target = l_buff == up ? down : up;

  unsigned int l_cur = left, r_cur = middle + 1;
  for (unsigned int i = left; i <= right; i++) {
    if (l_cur <= middle && r_cur <= right) {
      if (l_buff[l_cur] < r_buff[r_cur]) {
        target[i] = l_buff[l_cur];
        l_cur++;
      } else {
        target[i] = r_buff[r_cur];
        r_cur++;
      }
    } else if (l_cur <= middle) {
      target[i] = l_buff[l_cur];
      l_cur++;
    } else {
      target[i] = r_buff[r_cur];
      r_cur++;
    }
  }
  return target;
}
