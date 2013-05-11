#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include "converter.h"

void get_vector(char *message, float vector[], int length);
float eval(char *message, int length);
float cosin_sim(float a[], float b[], int length);

