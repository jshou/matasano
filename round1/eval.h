#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include "converter.h"

float count_eval(char *message, int length);
void get_vector(char *message, int messageLength, float vector[], int vectorLength);
float cosin_sim_freq_eval(char *message, int length);
float cosin_sim(float a[], float b[], int length);

