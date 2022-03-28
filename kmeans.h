
#ifndef KMEANS_H
#define KMEANS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "utils.h"
#include <omp.h>
#include <math.h> 


double dist2(double point1[], double point2[]);
double frob_dist(double **points1, double **points2,  int K);
u_int8_t label_point(double point[DIM], double **centroids,  int K);
void store_prev_centroids(double **prev_centroids, double **centroids,  int K);
void init_random_centroids(double **points,  double **centroids,  int K,  int MAX_POINTS);
double* compute_centroid(double **points, u_int8_t *clusters, int currentCluster, double centroid[DIM],  int MAX_POINTS);
void kmeans_lloyd(double **points, double **centroids, u_int8_t *clusters,  int K,  int MAX_POINTS);
//void kmeans_mcqueen(double points[MAX_POINTS][DIM], double centroids[K][DIM], u_int8_t clusters[MAX_POINTS]);

#endif