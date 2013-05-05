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
