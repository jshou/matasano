#include "xor.h"

void xor_decode(char *ciphertext, char *plaintext, int length, char key) {
  xor(ciphertext, plaintext, length, &key, 1);
}

void xor(char *ciphertext, char *plaintext, int length, char *key, int key_length) {
  for(int i = 0; i < length; i++) {
    plaintext[i] = ciphertext[i] ^ key[i % key_length];
  }
}
