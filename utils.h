

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define DIM 2 // actual dimension of data used in algo
#define TOL 1e-4


void read_data(char *filename, double **data, int MAX_POINTS);


#endif