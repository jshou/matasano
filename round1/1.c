#include <stdio.h>
#include <glib.h>

void main() {
  gchar *hexString = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  int hexLength = strlen(hexString);
  char *inp = (char*) malloc(hexLength/2);

  gchar *phexString = hexString;

  for (int i = 0; i < hexLength; i++) {
    sscanf(phexString, "%2x", &inp[i]);
    phexString += 2 * sizeof(char);
  }

  gchar *output = g_base64_encode(inp, strlen(hexString)/2);

  printf("%s", output);
}
