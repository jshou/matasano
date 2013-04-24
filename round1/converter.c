#include "converter.h"

void hexToByte(char* hexString, char* byteString) {
  int length = strlen(hexString);

  for (int i = 0; i < length/2; i++) {
    sscanf(hexString, "%2x", (unsigned int*) &byteString[i]);
    hexString += 2 * sizeof(char);
  }

  byteString[length] = 0;
}

void byteToHex(char* byteString, char* hexString, int byteLength) {
  for (int i = 0; i < byteLength*2; i += 2) {
    sprintf(&hexString[i], "%2x", (unsigned int) *byteString);
    byteString++;
  }

  hexString[byteLength*2] = 0;
}
