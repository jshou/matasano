void xor_decode(char *ciphertext, char *message, int length, char *key, int key_length);
int hamming_distance(char *a, char*b, int length);
char xor_best_key(char *ciphertext,
                  char *message,
                  int length,
                  float (*eval_func)(char *msg, int length));
