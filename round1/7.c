#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include <openssl/aes.h>
#include "7.h"

int main() {
  AES_KEY key;
  char *user_key = "YELLOW SUBMARINE";
  AES_set_decrypt_key(user_key, 128, &key);

  gsize length;
  guchar *ciphertext = g_base64_decode(MY_INPUT, &length);
  char *plaintext = malloc(length);

  for (int i = 0; i < length; i += 16) {
    AES_ecb_encrypt(ciphertext+i, plaintext+i, &key, AES_DECRYPT);
  }

  printf("%s\n", plaintext);
}
