
#ifndef KMEANS_H
#define KMEANS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "utils.h"

double inertia(double point1[], double point2[], int size);
void kmeans_lloyd(double data[MAX_POINTS][MAX_POINTS], u_int8_t k);

#endif