
#ifndef KMEANS_H
#define KMEANS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "utils.h"
#include <omp.h>
#include <math.h> 


double dist2(double point1[], double point2[]);
u_int8_t label_point(double point[DIM], double centroids[K][DIM]);
double* compute_centroid(double points[MAX_POINTS][DIM], u_int8_t clusters[MAX_POINTS], int currentCluster, double centroid[DIM]);
void kmeans_lloyd(double points[MAX_POINTS][DIM], double centroids[K][DIM], u_int8_t clusters[MAX_POINTS]);

#endif