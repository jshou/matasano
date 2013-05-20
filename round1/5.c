#include "converter.h"
#include "xor.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
  int length = strlen(plaintext);

  char *ciphertext = malloc(length);
  xor_decode(plaintext, ciphertext, length, "ICE", 3);

  char *hex = malloc(length * 2);
  byteToHex(ciphertext, hex, length);

  printf("%s\n", hex);
}
