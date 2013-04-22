#include <stdio.h>
#include <glib.h>

void main() {
  gchar *hexString = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

  int i, c = strlen(hexString);

  char *inp = (char*)malloc(c / 2);

  char *p1 = hexString;
  char *p2 = inp;

  for (i=0; i<c; i++) {
    *p2 = *p1<='9' ? *p1 - '0' : (*p1 + 10) - 'a';
    *p2 <<= 4;

    p1++;

    *p2 += *p1<='9' ? *p1 - '0' : (*p1 + 10) - 'a';

    p1++;
    p2++;
  }
  *p2 = 0;

  gchar *output = g_base64_encode(inp, strlen(hexString)/2);

  printf("%s", output);
}
