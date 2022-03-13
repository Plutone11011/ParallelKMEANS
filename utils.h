

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS 100000
#define MAX_FEATURES 1
#define DIM 2 // actual dimension of data used in algo
#define THREADS_P 4
#define THREADS_K 2
#define TOL 1e-4
#define K 7



void read_data(char *filename, double data[MAX_POINTS][MAX_FEATURES]);


#endif