#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include "converter.h"

void decode(char *ciphertext, char *message, int length, char key);
float eval(char *message, int length);
void get_vector(char *message, float vector[], int length);
float cosin_sim(float a[], float b[], int length);

void main() {
  char *cipherhex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  int length = strlen(cipherhex) / 2;
  char *ciphertext = malloc(length);

  hexToByte(cipherhex, ciphertext);

  float bestScore;
  int bestKey;
  char *bestMessage = malloc(length);
  char *currentMessage = malloc(length);

  for(int key = 0; key < 256; key++) {
    decode(ciphertext, currentMessage, length, (char) key); // key is 88

    int currentScore = eval(currentMessage, length);

    if (currentScore >= bestScore) {
      bestKey = key;
      bestScore = currentScore;
      strcpy(bestMessage, currentMessage);
    }


    printf("key: %d ", key);
    printf("score: %.2f ", currentScore);
    printf("message: %s\n", currentMessage);
  }

  printf("best key: %d ", bestKey);
  printf("best score: %.2f ", bestScore);
  printf("best message: %s\n", bestMessage);
}

void decode(char *ciphertext, char *plaintext, int length, char key) {
  for(int i = 0; i < length; i++) {
    plaintext[i] = ciphertext[i] ^ key;
  }
}

float english[] = {
  8.167,
  1.492,
  2.782,
  4.253,
  12.702,
  2.228,
  2.015,
  6.094,
  6.966,
  0.153,
  0.772,
  4.025,
  2.406,
  6.749,
  7.507,
  1.929,
  0.095,
  5.987,
  6.327,
  9.056,
  2.758,
  0.978,
  2.36,
  0.15,
  1.974,
  0.074
};

float eval(char *message, int length) {
  float vector[26] = {0.0};

  get_vector(message, vector, length);
  return cosin_sim(english, vector, 26);
}

void get_vector(char *message, float vector[], int length) {
  for (int i = 0; i < length; i++) {
    char c = tolower(message[i]);
    if (isalpha(c)) {
      vector[c - 'a']++;
    }
  }

  for (int i = 0; i < 26; i++) {
    vector[i] /= (float) length;
    vector[i] *= 100.0; // percentage
  }
}

float cosin_sim(float a[], float b[], int length) {
  float numerator = 0.0;
  float sum_a = 0.0;
  float sum_b = 0.0;

  for (int i = 0; i < length; i++) {
    numerator += a[i] * b[i];
    sum_a += a[i] * a[i];
    sum_b += b[i] * b[i];
  }

  float denom = sqrtf(sum_a) * sqrtf(sum_b);

  if (denom) {
    return numerator / denom;
  } else {
    return 0.0;
  }
}
