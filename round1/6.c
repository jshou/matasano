#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <stdlib.h>
#include <limits.h>
#include "xor.h"
#include "eval.h"
#include "6.h"

void best_key_size(int *key_sizes, int num_keys, char *input);
float normalized_edit_distance(char *input, int keysize);
void transpose_blocks(char **blocks, int* block_sizes, int key_size, int block_size, char *ciphertext, int length);

int main() {
  // decode ciphertext
  gsize length;
  guchar *ciphertext = g_base64_decode(MY_INPUT, &length);

  // get key size
  int *key_sizes = malloc(sizeof(int) * 3);
  best_key_size(key_sizes, 3, ciphertext);

  int key_size = 29;

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

void best_key_size(int *key_sizes, int num_keys, char *input) {
  // max out key_sizes
  for (int i = 0; i < num_keys; i++) {
    key_sizes[i] = 0;
  }
  float best_edit_distance = INT_MAX;

  // iterate over best key sizes
  for (int key_size = 2; key_size <= 40; key_size++) {
    float dist = normalized_edit_distance(input, key_size);
    if (dist < best_edit_distance) {
      best_edit_distance = dist;

      // shift key sizes
      for (int i = num_keys - 1; i > 0; i--) {
        key_sizes[i] = key_sizes[i-1];
      }

      // save best key size
      key_sizes[0] = key_size;
    }
  }
}

// the following function assumes twice keysize is smaller than strlen(input)
float normalized_edit_distance(char *input, int keysize) {
  // initialize blocks
  int num_blocks = 2;
  char **blocks = malloc(sizeof(char*) * num_blocks);

  for (int i = 0; i < keysize; i++) {
    for (int j = 0; j < num_blocks; j++) {
      char *curr_block = blocks[j] = malloc(keysize);
      curr_block[i] = input[j*keysize + i];
    }
  }

  // get average distances
  int numerator = 0;
  for (int i = 0; i < num_blocks; i++) {
    for (int j = 0; j < i; j++) {
      numerator += hamming_distance(blocks[i], blocks[j], keysize);
    }
  }
  float avg_dist = ((float) numerator) / ((float) num_blocks * (num_blocks + 1) / 2);

  // free the blocks
  for (int i = 0; i < num_blocks; i++) {
    free(blocks[i]);
  }
  free(blocks);

  // normalize by keysize
  return ((float) avg_dist) / ((float) keysize);
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
