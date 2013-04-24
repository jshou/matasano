#include "converter.h"

void hexToByte(char* hexString, char* byteString) {
  while (*hexString) {
    sscanf(hexString, "%2x", (unsigned int*) byteString);
    hexString += 2;
    byteString++;
  }
}

void byteToHex(char* byteString, char* hexString, int byteLength) {
  for (int i = 0; i < byteLength*2; i += 2) {
    sprintf(&hexString[i], "%2x", (unsigned int) *byteString);
    byteString++;
  }

  hexString[byteLength*2] = 0;
}
