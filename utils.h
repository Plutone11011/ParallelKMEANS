

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS 100
#define MAX_FEATURES 9
#define DIM 2 // actual dimension of data used in algo
#define LAT 6 // index in csv column for latitude
#define LONG 7 // index in csv column for longitude

void read_csv(char *filename, double data[MAX_POINTS][MAX_FEATURES]);

#endif