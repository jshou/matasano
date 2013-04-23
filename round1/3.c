#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "converter.h"

void decode(char *ciphertext, char *message, int length, char key);
float eval(char *message, int length);

void main() {
  char *cipherhex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  int length = strlen(cipherhex) / 2;
  char *ciphertext = malloc(length);

  hexToByte(cipherhex, ciphertext);

  float bestScore;
  char bestKey;
  char *bestMessage = malloc(length);
  char *currentMessage = malloc(length);

  for(int i = 0; i < CHAR_MAX; i++) {
    char key = (char) i;
    decode(ciphertext, currentMessage, length, key);

    float currentScore = eval(currentMessage, length);
    if (currentScore > bestScore) {
      bestScore = currentScore;
      bestMessage = currentMessage;
    }
  }

  printf("%s\n", bestMessage);
}

void decode(char *ciphertext, char *plaintext, int length, char key) {
  for(int i = 0; i < length; i++) {
    plaintext[i] = ciphertext[i] ^ key;
  }
}

float eval(char *message, int length) {
  float count;

  for(int i = 0; i < length; i++) {
    if (message[i] == 'e') {
      count++;
    }
  }

  return count;
}
