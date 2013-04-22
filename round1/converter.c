#include "converter.h"

void hexToByte(char* hexString, char* byteString) {
  int length = strlen(hexString);

  for (int i = 0; i < length; i++) {
    sscanf(hexString, "%2x", (unsigned int*) &byteString[i]);
    hexString += 2 * sizeof(char);
  }
}

void byteToHex(char* byteString, char* hexString) {
  int length = strlen(byteString) * 2;
  for (int i = 0; i < length; i += 2) {
    sprintf(&hexString[i], "%2x", (unsigned int) *byteString);
    byteString++;
  }
}
