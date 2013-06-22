#include "xor.h"
#include "eval.h"

void main() {
  char *cipherhex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  int length = strlen(cipherhex) / 2;
  char *ciphertext = malloc(length);
  char *message = malloc(length);

  hexToByte(cipherhex, ciphertext);

  char bestKey = xor_best_key(ciphertext, message, length, &count_eval);

  printf("best key: %d\n", bestKey);
  printf("best message: %s\n", message);
}
