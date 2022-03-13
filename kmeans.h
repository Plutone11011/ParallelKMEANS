
#ifndef KMEANS_H
#define KMEANS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "utils.h"
#include <omp.h>
#include <math.h> 


double dist2(double point1[], double point2[]);
double frob_dist(double points1[K][DIM], double points2[K][DIM]);
u_int8_t label_point(double point[DIM], double centroids[K][DIM]);
void store_prev_centroids(double prev_centroids[K][DIM], double centroids[K][DIM]);
void init_random_centroids(double points[MAX_POINTS][DIM],  double centroids[K][DIM]);
double* compute_centroid(double points[MAX_POINTS][DIM], u_int8_t clusters[MAX_POINTS], int currentCluster, double centroid[DIM]);
void kmeans_lloyd(double points[MAX_POINTS][DIM], double centroids[K][DIM], u_int8_t clusters[MAX_POINTS]);
//void kmeans_mcqueen(double points[MAX_POINTS][DIM], double centroids[K][DIM], u_int8_t clusters[MAX_POINTS]);

#endif