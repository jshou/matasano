#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include <limits.h>
#include "xor.h"
#include "eval.h"
#include "6.h"

int best_key_size(char *input);
float normalized_edit_distance(char *input, int keysize);
void transpose_blocks(char *blocks[], int key_size, int block_size, char *ciphertext, int length);

int main() {
  // decode ciphertext
  gsize l;
  guchar *ciphertext = g_base64_decode(MY_INPUT, &l);
  int length = strlen(ciphertext);

  // get key size
  int key_size = best_key_size(ciphertext);

  // transpose blocks
  int block_size = length / key_size;
  char *blocks[key_size];
  transpose_blocks(blocks, key_size, block_size, ciphertext, length);

  // solve each block
  char *key = malloc(key_size);
  for (int i = 0; i < key_size; i++) {
    char *current_block = blocks[i];
    char best_key_section;
    float best_score;

    if (i == key_size - 1) {
      block_size = length % key_size;
    }

    char *message = malloc(block_size);
    key[i] = xor_best_key(current_block, message, block_size, &count_eval);
    free(message);
  }

  char *plaintext = malloc(length);
  xor_decode(ciphertext, plaintext, length, key, key_size);

  printf("key: %s\n", key);
  printf("msg: %s\n", plaintext);
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
  free(first);
  free(second);

  return ((float) distance) / ((float) keysize);
}

void transpose_blocks(char *blocks[], int key_size, int block_size, char *ciphertext, int length) {
  for (int offset = 0; offset < key_size; offset++) {
    char *current_block = blocks[offset];
    current_block = malloc(block_size);

    for (int j = 0; j < block_size; j++) {
      int index = j * block_size + offset;
      if (index > length) { break; }
      current_block[j] = ciphertext[index];
    }
  }
};
