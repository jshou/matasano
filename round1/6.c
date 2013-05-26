#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "xor.h"
#include "6.h"

char *get_input();

int main() {
  gsize length;
  guchar *ciphertext = g_base64_decode(MY_INPUT, &length);

  printf("%s\n", ciphertext);
}
