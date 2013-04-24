#include <stdio.h>
#include <stdlib.h>
#include "converter.h"

void main() {
  char *a = "1c0111001f010100061a024b53535009181c";
  char *b = "686974207468652062756c6c277320657965";
  int length = strlen(a);

  char *byteA = (char*) malloc(length/2);
  char *byteB = (char*) malloc(length/2);

  hexToByte(a, byteA);
  hexToByte(b, byteB);

  char *byteOutput = (char*) malloc(length/2);
  char *output = (char*) malloc(length + 1);

  // A xor B
  for (int i = 0; i < strlen(a)/2; i++) {
    byteOutput[i] = byteA[i] ^ byteB[i];
  }

  byteToHex(byteOutput, output, length/2);

  printf("%s\n", output);
}
