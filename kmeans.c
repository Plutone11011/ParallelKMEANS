#include "kmeans.h"

double dist2(double point1[DIM], double point2[DIM]){
    // useless to parallelize, number of dimensions very small
    // for k-means.
    double res = 0;
    for (int i = 0; i < DIM; i++){
        res += (point1[i] - point2[i])*(point1[i] - point2[i]);
    }
    
    return res;
    
}

u_int8_t label_point(double point[DIM], double centroids[K][DIM]){
    // data dependency here, the inner loop instruction depends on 
    // previous value of point_centroid, not parallelizable
    int point_centroid = 0;
    for (int k = 0; k < K; k++){
        //printf("from centroid %d: %lf \n", k, dist2(point, centroids[k]));
        if (dist2(point, centroids[k]) < dist2(point, centroids[point_centroid])){
            point_centroid = k;
        }
    }
    //printf("Minimum distance centroid %d\n", point_centroid);   
    return point_centroid;
}

double* compute_centroid(double points[MAX_POINTS][DIM], u_int8_t clusters[MAX_POINTS], int currentCluster, double centroid[DIM]){
    // compute mean of all points belonging to cluster 
    // according to current clustering
    double sum = 0 ;
    int nPointsInCluster = 0;
    for (int j = 0; j < DIM; j++){
        // parallelizable, reduction
//        #pragma omp parallel for schedule(dynamic) 
        for (int i = 0; i < MAX_POINTS; i++){
            // if current point's cluster is 
            // the one we want to recompute
            // then accumulate
            if (clusters[i] == currentCluster){
                sum += points[i][j];
                nPointsInCluster++;
            }
            
        }
        if (sum != 0 && nPointsInCluster != 0){
            // if there are no points in currentCluster
            // maintain same centroid 
            //printf("Centroid dimension %d= %lf / %d\n", j, sum, nPointsInCluster);
            centroid[j] = sum / nPointsInCluster;
        }
        nPointsInCluster = 0;
        sum = 0;
    }
}

void kmeans_lloyd(double points[MAX_POINTS][DIM],  double centroids[K][DIM], u_int8_t clusters[MAX_POINTS]){
    /*
    * Computes k means on a number of clusters defined by K and with
    * points points of dimension DIM
    */
    srand(time(NULL));
    // pick centroids randomly selected from points 
    int rand_point_i;
    // parallelize a possibly very small set of tasks depending on number of clusters
    // experiment? also number of dimensions, generally small
    #pragma omp parallel for private(rand_point_i) schedule(static) num_threads(THREADS_K)
    for (int k = 0; k < K; k++){
        rand_point_i = rand() % MAX_POINTS;
        for (int j = 0; j < DIM; j++){
            //printf("Centroid %d for thread %d\n", k, omp_get_thread_num());
            centroids[k][j] = points[rand_point_i][j];
        } 
    }

    
    const int max_iter = 10000; // usually condition to stop is also that difference for centroid is too small   
    int iter = 0;
    double prev_centroids[K][DIM];
    double frob_distance;
    do {
        // keep a copy of centroids previous value
        for (int k = 0; k < K; k++){
            for (int j = 0; j < DIM; j++){
                prev_centroids[k][j] = centroids[k][j];
            }
        }
        // for each point, label it, that is, for each centroid
        // find the one closest in euclidean distance from the current point
        #pragma omp parallel for schedule(dynamic) num_threads(THREADS_P)
        for (int i = 0; i < MAX_POINTS; i++){
            //printf("Distance of point %d, thread %d \n", i, omp_get_thread_num());
            clusters[i] = label_point(points[i], centroids);
            //printf("Cluster %d for point %d\n", clusters[i], i);
        }
        // need for all points to be labeled before 
        #pragma omp parallel for schedule(dynamic) num_threads(THREADS_K)
        for (int k = 0; k < K; k++){
            //printf("Cluster %d for thread %d\n", k, omp_get_thread_num());
            compute_centroid(points, clusters, k, centroids[k]);
        }
        frob_distance = 0; // frobenius norm of the distance used for tolerance
        for (int k = 0; k < K; k++){
            //printf("Previous (%lf, %lf)\nCurrent (%lf, %lf)\n",prev_centroids[k][0], prev_centroids[k][1], centroids[k][0], centroids[k][1]);
            frob_distance += dist2(centroids[k], prev_centroids[k]);
        }
        frob_distance = sqrt(frob_distance);
        //printf("Error %lf\n", frob_distance);
        iter++;
    }  while (iter < max_iter && frob_distance > TOL);
    //printf("Iterations done: %d\n", iter);
}