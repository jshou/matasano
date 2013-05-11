#include <stdio.h>
#include "xor.h"
#include "eval.h"

int main() {
  size_t n = sizeof(char) * 60;
  char *lineptr = malloc(n);

  while(getline(&lineptr, &n, stdin) != -1) {
    printf("%s", lineptr);
  }
}
