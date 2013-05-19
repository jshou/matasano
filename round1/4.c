#define _GNU_SOURCE
#include "xor.h"
#include "eval.h"
#include <stdio.h>

int main() {
  size_t n = sizeof(char) * 60;
  int messageLength = n / 2;
  char *lineptr = malloc(n);

  int currentIndex = 0;

  while(getline(&lineptr, &n, stdin) != -1) {
    // try all keys for this line
    float lineScore;
    float lineBest;
    char *lineMessage = malloc(messageLength);
    char *bestLineMessage = malloc(messageLength);

    for (int key = 0; key < 256; key++) {
      xor_decode(lineptr, lineMessage, messageLength, (char) key);
      float lineScore = cosin_sim_freq_eval(lineMessage, messageLength);

      if (lineScore > lineBest) {
        lineBest = lineScore;
        strcpy(bestLineMessage, lineMessage);
      }
    }

    printf("current best message: %d: %s\n", currentIndex, bestLineMessage);

    free(lineMessage);
    free(bestLineMessage);

    currentIndex++;
  }
}
