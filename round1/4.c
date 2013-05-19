#define _GNU_SOURCE
#include "xor.h"
#include "eval.h"
#include <stdio.h>

int main() {
  size_t n = sizeof(char) * 60;
  int messageLength = n/2;
  char *lineptr = malloc(n);
  char *ciphertext = malloc(messageLength);

  float currentScore;
  float bestScore;
  char *currentMessage = malloc(messageLength);
  char *bestMessage = malloc(messageLength);
  int currentIndex = 0;
  int messageIndex = 0;

  while(getline(&lineptr, &n, stdin) != -1) {
    for (int key = 0; key < 256; key++) {
      hexToByte(lineptr, ciphertext);
      xor_decode(ciphertext, currentMessage, messageLength, (char) key);
      float currentScore = count_eval(currentMessage, messageLength);

      if (currentScore > bestScore) {
        bestScore = currentScore;
        strcpy(bestMessage, currentMessage);
        messageIndex = currentIndex;
      }
    }

    currentIndex++;
  }

  printf("best score: %.2f\n", bestScore);
  printf("best message: %d: %s\n", messageIndex, bestMessage);
}
