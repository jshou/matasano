#include "xor.h"

void xor_decode(char *ciphertext, char *plaintext, int length, char *key, int key_length) {
  for(int i = 0; i < length; i++) {
    plaintext[i] = ciphertext[i] ^ key[i % key_length];
  }
}

int hamming_distance(char *a, char*b, int length) {
  int distance = 0;

  for(int i = 0; i < length; i++) {
    if (a[i] != b[i]) {
      distance++;
    }
  }

  return distance;
}
