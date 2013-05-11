#include "xor.h"
#include "eval.h"

void main() {
  char *cipherhex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  int length = strlen(cipherhex) / 2;
  char *ciphertext = malloc(length);

  hexToByte(cipherhex, ciphertext);

  float bestScore;
  int bestKey;
  char *bestMessage = malloc(length);
  char *currentMessage = malloc(length);

  for(int key = 0; key < 256; key++) {
    xor_decode(ciphertext, currentMessage, length, (char) key); // key is 88

    float currentScore = eval(currentMessage, length);

    if (currentScore >= bestScore) {
      bestKey = key;
      bestScore = currentScore;
      strcpy(bestMessage, currentMessage);
    }
  }

  printf("best key: %d\n", bestKey);
  printf("best score: %.2f\n", bestScore);
  printf("best message: %s\n", bestMessage);
}
