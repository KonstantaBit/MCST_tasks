#include <bits/types/stack_t.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 512

void parse(char[], char[]);

struct Pair {
  char symbol;
  int state;
};

int calculate(char[], struct Pair *, size_t);

int main(int argc, char *argv[]) {
  size_t size;

  printf("Enter the number of variables: ");

  scanf("%zu", &size);

  char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  int cnt_pairs = (size < 26) ? size : 26;

  struct Pair *pairs = calloc(cnt_pairs, sizeof(struct Pair));
  printf("Enter 0 for false, 1 for true\nAfter enter a logical expression\n");
  for (int i = 0; i < cnt_pairs; ++i) {
    int temp;
    printf("%c = ", (int)alphabet[i]);
    scanf("%d ", &temp);
    struct Pair pair = {alphabet[i], temp};
    pairs[i] = pair;
  }
  char str[SIZE] = "";
  fgets(str, SIZE, stdin);
  printf("%s\n", str);
  char buf[SIZE] = "";

  parse(str, buf);

  printf("RESULT:  %d\n", calculate(buf, pairs, size));
  free(pairs);
  return EXIT_SUCCESS;
}

void parse(char data[], char out[]) {
  char stack[SIZE] = "";
  int stack_end = 0;
  int out_end = 0;
  int lenght = strnlen(data, SIZE);

  for (int i = 0; i < lenght; ++i) {
    if (i + 2 < lenght && data[i] == 'A' && data[i + 1] == 'N' &&
        data[i + 2] == 'D') {
      while (stack_end - 1 > -1 && (stack[stack_end - 1] == '-')) {
        out[out_end] = stack[stack_end - 1];
        out_end += 1;
        stack_end -= 1;
      }
      stack[stack_end] = '*';
      stack_end += 1;
      i += 3;
    } else if (i + 2 < lenght && data[i] == 'N' && data[i + 1] == 'O' &&
               data[i + 2] == 'T') {
      stack[stack_end] = '-';
      stack_end += 1;
      i += 3;
    } else if (i + 1 < lenght && data[i] == 'O' && data[i + 1] == 'R') {
      while (stack_end - 1 > -1 &&
             (stack[stack_end - 1] == '-' || stack[stack_end - 1] == '*')) {
        out[out_end] = stack[stack_end - 1];
        out_end += 1;
        stack_end -= 1;
      }
      stack[stack_end] = '+';
      stack_end += 1;
      i += 2;
    } else if (data[i] == '(') {
      stack[stack_end] = '(';
      stack_end += 1;
    } else if (data[i] == ')') {
      while (stack[stack_end - 1] != '(') {
        out[out_end] = stack[stack_end - 1];
        out_end += 1;
        stack_end -= 1;
      }
      stack_end -= 1;
    } else if (isalpha(data[i])) {
      out[out_end] = data[i];
      out_end += 1;
    }
  }
  while (stack_end != 0) {
    out[out_end] = stack[--stack_end];
    out_end += 1;
  }
  return;
}

int calculate(char in[], struct Pair *pairs, size_t size) {
  char stack[SIZE] = "";
  int stack_end = 0;

  for (int i = 0; i < strnlen(in, SIZE); ++i) {
    if (isalpha(in[i])) {
      for (int j = 0; j < size; ++j) {
        if (pairs[i].symbol == in[i]) {
          stack[stack_end] = pairs[i].state + '0';
          stack_end += 1;
        }
      }
    } else if (in[i] == '-') {
      stack[stack_end - 1] = atoi(&stack[stack_end - 1]) ? '0' : '1';
    } else if (in[i] == '*') {
      stack[stack_end - 1] =
          (atoi(&stack[stack_end - 1]) && atoi(&stack[stack_end - 2])) + '0';
      stack_end -= 2;
    } else if (in[i] == '+') {
      stack[stack_end - 1] =
          (atoi(&stack[stack_end - 1]) || atoi(&stack[stack_end - 2])) + '0';
      stack_end -= 2;
    }
  }
  return (int)stack[0] == 49;
}
