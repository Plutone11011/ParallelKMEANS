#include "kmeans.h"

double dist2(double point1[DIM], double point2[DIM]){
    // trivial parallelization
    // number of dimensions very small
    // for k-means.
    double res = 0;
    for (int i = 0; i < DIM; i++){
        res += (point1[i] - point2[i])*(point1[i] - point2[i]);
    }
    
    return res;
    
}

double frob_dist(double **points1, double **points2,  int K){
    double dist = 0;
    #pragma omp parallel reduction(+:dist) 
    {
        int my_start = K*(omp_get_thread_num() / omp_get_num_threads());
        int my_end = K*((omp_get_thread_num()+1) / omp_get_num_threads());
        long my_dist = 0; 
        for (int i = my_start; i < my_end; i++){
            my_dist += dist2(points1[i], points2[i]); 
        }
        dist += my_dist;
    }
    return sqrt(dist);


}

u_int8_t label_point(double point[DIM], double **centroids,  int K){
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

double* compute_centroid(double **points, u_int8_t *clusters, int currentCluster, double centroid[DIM],  int MAX_POINTS){
    /* compute mean of all points belonging to cluster 
    * according to current clustering
    */
    double sum = 0 ;
    int nPointsInCluster = 0;
    for (int j = 0; j < DIM; j++){
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

void store_prev_centroids(double **prev_centroids, double **centroids,  int K){
    // keep a copy of centroids previous value
    #pragma omp parallel for schedule(dynamic)
    for (int k = 0; k < K; k++){
        for (int j = 0; j < DIM; j++){
            prev_centroids[k][j] = centroids[k][j];
        }
    }
}

void init_random_centroids(double **points,  double **centroids,  int K,  int MAX_POINTS){
    // parallelize a possibly very small set of tasks depending on number of clusters
    // experiment? also number of dimensions, generally small
    int rand_point_i;
    #pragma omp parallel for private(rand_point_i) schedule(static)
    for (int k = 0; k < K; k++){
        rand_point_i = rand() % MAX_POINTS;
        for (int j = 0; j < DIM; j++){
            //printf("Centroid %d for thread %d\n", k, omp_get_thread_num());
            centroids[k][j] = points[rand_point_i][j];
        } 
    }
}

void kmeans_lloyd(double **points, double **centroids, u_int8_t *clusters,  int K,  int MAX_POINTS){
    /*
    * Computes k means on a number of clusters defined by K and with
    * points points of dimension DIM
    */
    srand(time(NULL));
    init_random_centroids(points, centroids, K, MAX_POINTS);
    // pick centroids randomly selected from points 
    
    const int MAX_ITER = 1000; 
    int iter = 0;
    double frob_distance;
    
    double **prev_centroids;
    prev_centroids = malloc(K * sizeof *prev_centroids);
    for (int i=0; i<K; i++)
    {
        prev_centroids[i] = malloc(DIM * sizeof *prev_centroids[i]);
    }
    
    do {
        store_prev_centroids(prev_centroids, centroids, K);
        // for each point, label it, that is, for each centroid
        // find the one closest in euclidean distance from the current point
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < MAX_POINTS; i++){
            //printf("Distance of point %d, thread %d \n", i, omp_get_thread_num());
            clusters[i] = label_point(points[i], centroids, K);
            //printf("Cluster %d for point %d\n", clusters[i], i);
        }
        #pragma omp parallel for schedule(dynamic)
        for (int k = 0; k < K; k++){
            //printf("Cluster %d for thread %d\n", k, omp_get_thread_num());
            compute_centroid(points, clusters, k, centroids[k], MAX_POINTS);
        }
        // frobenius norm of the distance used for tolerance
        frob_distance = frob_dist(centroids, prev_centroids, K);
        //printf("Error %lf\n", frob_distance);
        iter++;
    }  while (iter < MAX_ITER && frob_distance > TOL);
    //printf("Iterations done: %d\n", iter);
}
