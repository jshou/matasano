#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "converter.h"

void decode(char *ciphertext, char *message, int length, char key);
int eval(char *message, int length);

void main() {
  char *cipherhex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  int length = strlen(cipherhex) / 2;
  char *ciphertext = malloc(length);

  hexToByte(cipherhex, ciphertext);

  int bestScore;
  int bestKey;
  char *bestMessage = malloc(length);
  char *currentMessage = malloc(length);

  for(int key = 0; key < 256; key++) {
    decode(ciphertext, currentMessage, length, (char) key); // key is 88

    int currentScore = eval(currentMessage, length);

    if (currentScore >= bestScore) {
      bestKey = key;
      bestScore = currentScore;
      strcpy(bestMessage, currentMessage);
    }
  }

  printf("%d ", bestKey);
  printf("%d ", bestScore);
  printf("%s\n", bestMessage);
}

void decode(char *ciphertext, char *plaintext, int length, char key) {
  for(int i = 0; i < length; i++) {
    plaintext[i] = ciphertext[i] ^ key;
  }
}

int eval(char *message, int length) {
  int count = 0;

  for(int i = 0; i < length; i++) {
    if (!isalnum(message[i]) && !isspace(message[i]) && !(message[i] == '\'')) {
      return 0;
    } else if (message[i] == 'e' || message[i] == 'E' || message[i] == 's' || message[i] == 'S') {
      count++;
    }
  }

  return count;
}
