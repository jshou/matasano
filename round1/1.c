#include <stdio.h>
#include <glib.h>
#include "converter.h"

void main() {
  gchar *hexString = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  int length = strlen(hexString);
  char *byteString = (char*) malloc(length/2);
  hexToByte(hexString, byteString);

  gchar *output = g_base64_encode(byteString, length/2);

  printf("%s\n", output);

  guchar *byteString2 = g_base64_decode(output, (gsize *) malloc(40));
  char *hexString2 = (char*) malloc(length);
  byteToHex(byteString2, hexString2);
  printf("%s\n", hexString2);
}
