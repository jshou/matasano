#include <stdlib.h>
#include <string.h>
#include "xor.h"

void xor_decode(char *ciphertext, char *plaintext, int length, char *key, int key_length) {
  for(int i = 0; i < length; i++) {
    plaintext[i] = ciphertext[i] ^ key[i % key_length];
  }
}

int hamming_distance(char *a, char *b, int length) {
  int distance = 0;

  for(int i = 0; i < length; i++) {
    if (a[i] != b[i]) {
      distance++;
    }
  }

  return distance;
}

char xor_best_key(char *ciphertext,
                  char *message,
                  int length,
                  float (*eval_func)(char *msg, int length)) {
  char bestKey;
  float bestScore;
  char *currentMessage = malloc(length);

  for(int key = 0; key < 256; key++) {
    char charkey = (char) key;
    xor_decode(ciphertext, currentMessage, length, &charkey, 1);

    float currentScore = eval_func(currentMessage, length);

    if (currentScore >= bestScore) {
      bestKey = key;
      bestScore = currentScore;
      strncpy(message, currentMessage, length);
    }
  }

  free(currentMessage);

  return bestKey;
}
