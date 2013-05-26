#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include <limits.h>
#include "xor.h"
#include "6.h"

int best_key_size(char *input);
float normalized_edit_distance(char *input, int keysize);

int main() {
  // decode ciphertext
  gsize length;
  guchar *ciphertext = g_base64_decode(MY_INPUT, &length);

  // get key size
  int key_size = best_key_size(ciphertext);

  // transpose blocks
}

int best_key_size(char *input) {
  int best_key_size = 0;
  float best_edit_distance = INT_MAX;

  for (int key_size = 2; key_size <= 40; key_size++) {
    float dist = normalized_edit_distance(input, key_size);
    if (dist < best_edit_distance) {
      best_edit_distance = dist;
      best_key_size = key_size;
    }
  }

  return best_key_size;
}

// the following function assumes twice keysize is smaller than strlen(input)
float normalized_edit_distance(char *input, int keysize) {
  // initialize blocks
  char *first = malloc(keysize);
  char *second = malloc(keysize);

  for (int i = 0; i < keysize; i++) {
    first[i] = input[i];
    second[i] = input[keysize + i];
  }

  int distance = hamming_distance(first, second, keysize);
  return ((float) distance) / ((float) keysize);
}
