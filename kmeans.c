#include "kmeans.h"

double dist2(double point1[DIM], double point2[DIM]){
    
    double res = 0;
    for (int i = 0; i < DIM; i++){
        printf("Distance between points (%lf, %lf)\n", point1[i], point2[2]);
        res += (point1[i] - point2[i])*(point1[i] - point2[i]);
    }
    
    return res;
    
}

u_int8_t label_point(double point[DIM], double centroids[K][DIM]){
    int point_centroid = 0;  
    for (int k = 0; k < K; k++){
        // actually should record min distance and not compute twice
        if (dist2(point, centroids[k]) < dist2(point, centroids[point_centroid])){
            point_centroid = k;
        }
    }   
    return point_centroid;
}

double *compute_centroid(double points[MAX_POINTS][DIM], u_int8_t clusters[MAX_POINTS], int currentCluster, double centroid[DIM]){
    // compute mean of all points belonging to cluster 
    // according to current clustering
    int sum ;
    int nPointsInCluster = 0;
    for (int j = 0; j < DIM; j++){
        sum = 0 ;
        for (int i = 0; i < MAX_POINTS; i++){
            // if current point's cluster is the one we want to recompute
            // then accumulate
            if (clusters[i] == currentCluster){
                sum += points[i][j];
                nPointsInCluster++;
            }
        }
        centroid[j] = sum / nPointsInCluster;
        nPointsInCluster = 0;
        sum = 0;
    }
}

void kmeans_lloyd(double points[MAX_POINTS][DIM],  double centroids[K][DIM]){
    /*
    * Computes k means on a number of clusters defined by K and with
    * points points of dimension DIM
    */
    srand(time(NULL));
    // pick centroids at random from points points
    int rand_point_i;
    for (int k = 0; k < K; k++){
        rand_point_i = rand() % MAX_POINTS;
        for (int j = 0; j < DIM; j++){
            
           centroids[k][j] = points[rand_point_i][j];
        } 
    }

    u_int8_t clusters[MAX_POINTS] = {0};
    int max_iter = 1000; // usually condition to stop is also that difference for centroid is too small   

    for (int iter = 0; iter < max_iter; iter++){
        for (int i = 0; i < MAX_POINTS; i++){
            clusters[i] = label_point(points[i], centroids);
        }
        for (int k = 0; k < K; k++){
            compute_centroid(points, clusters, k, centroids[k]);
        }
    }
}