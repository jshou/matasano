void hexToByte(char* hexString, char* byteString) {
  int length = strlen(hexString);

  for (int i = 0; i < length; i++) {
    sscanf(hexString, "%2x", &byteString[i]);
    hexString += 2 * sizeof(char);
  }
}

char* byteToHex(char* byteString) {
}
