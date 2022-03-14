

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS 200000
#define DIM 2 // actual dimension of data used in algo
#define THREADS 4
#define TOL 1e-4
#define K 16
#define LLOYD "lloyd"
#define MCQUEEN "mcqueen"


void read_data(char *filename, double data[MAX_POINTS][DIM]);


#endif