#include "eval.h"

float count_eval(char *message, int length) {
  float count = 0.0;

  for (int i = 0; i < length; i++) {
    char c = message[i];

    if (c == ' ' || c == 'e' || c == 't') {
      count += 1.0;
    }
  }

  return count;
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
  0.074,
  13.0 // guessing at freq of space, slightly more than e
};

float cosin_sim_freq_eval(char *message, int length) {
  int n = 1;
  int combinations = pow(26, n);
  float vector[combinations + 1];
  for (int i = 0; i < combinations; i++) { vector[i] = 0.0; }

  get_vector(message, length, vector, combinations + 1);
  return cosin_sim(english, vector, combinations + 1);
}

void get_vector(char *message, int messageLength, float vector[], int vectorLength) {
  for (int i = 0; i < messageLength; i++) {
    char c = tolower(message[i]);
    if (isalpha(c)) {
      vector[c - 'a']++;
    } else if (c == ' ' || c == '\n') {
      vector[vectorLength]++;
    }
  }

  for (int i = 0; i < 26; i++) {
    vector[i] /= (float) messageLength;
    vector[i] *= 100.0; // percentage
  }
}

int get_ngram_key(char *ngram, int length) {
  int key = 0;

  for (int i = 0; i < length; i++) {
    key += ngram[i - 'a'] * pow(26, length - i);
  }

  return key;
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

