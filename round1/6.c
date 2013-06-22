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
void transpose_blocks(char **blocks, int* block_sizes, int key_size, int block_size, char *ciphertext, int length);

int main() {
  // decode ciphertext
  gsize length;
  guchar *ciphertext = g_base64_decode(MY_INPUT, &length);

  // get key size
  int key_size = best_key_size(ciphertext);

  // transpose blocks
  int max_block_size = length / key_size + 1;
  char **blocks = malloc(sizeof(char*) * key_size);
  int *block_sizes = malloc(sizeof(int*) * key_size);

  transpose_blocks(blocks, block_sizes, key_size, max_block_size, ciphertext, length);

  // solve each block
  char *key = malloc(key_size);
  for (int i = 0; i < key_size; i++) {

    char *message = malloc(block_sizes[i]);
    key[i] = xor_best_key(blocks[i], message, block_sizes[i], &count_eval);
    free(message);
  }

  char *plaintext = malloc(length);
  xor_decode(ciphertext, plaintext, length, key, key_size);

  printf("keysize: %d\n", key_size);
  printf("key: %s\n", key);
  printf("msg: %s\n", plaintext);
}

int best_key_size(char *input) {
  int best_key_size;
  // max out key_sizes
  float best_edit_distance = INT_MAX;

  // iterate over best key sizes
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
  int num_blocks = 3;
  char **blocks = malloc(sizeof(char*) * num_blocks);

  for (int i = 0; i < num_blocks; i++) {
    char *curr_block = blocks[i] = malloc(keysize);
    for (int j = 0; j < keysize; j++) {
      curr_block[j] = input[i*keysize + j];
    }
  }

  // get average distances
  int numerator = 0;
  int denom = 0;
  for (int i = 0; i < num_blocks; i++) {
    for (int j = 0; j < i; j++) {
      numerator += hamming_distance(blocks[i], blocks[j], keysize);
      denom++;
    }
  }

  // free the blocks
  for (int i = 0; i < num_blocks; i++) {
    free(blocks[i]);
  }
  free(blocks);

  float score = ((float) numerator) / ((float) denom) / ((float) keysize);
  return score;
}

void transpose_blocks(char **blocks, int *block_sizes, int key_size, int max_block_size, char *ciphertext, int length) {
  for (int key_idx = 0; key_idx < key_size; key_idx++) {
    char *block = blocks[key_idx] = malloc(max_block_size);
    int block_size = 0;

    while(1) {
      int index = block_size * key_size + key_idx;
      if (index >= length) {break;}
      block[block_size] = ciphertext[index];
      block_size++;
    }
    block_sizes[key_idx] = block_size - 1;
  }
}
