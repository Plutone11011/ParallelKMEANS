

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS 100
#define MAX_FEATURES 9

void read_csv(char *filename, double data[MAX_POINTS][MAX_FEATURES]);

#endif