/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/


#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include "kmeans.h"
#include "utils.h"


//const int XSIZE = 800, YSIZE = 600; 
/**const int XSIZE = 1024, YSIZE = 768;

typedef struct {
    int r, g, b;
} pixel_t; 

const pixel_t colors[] = {
    {255, 0, 0},
    {0, 0, 255},
    {0, 255, 0},
    {255,255,0},
    {0,255,255}};
const int NCOLORS = sizeof(colors)/sizeof(colors[0]);

void draw_point(double x, double y, u_int8_t cluster, u_int8_t isCluster){
        
    if (!isCluster){
        gfx_color(colors[cluster].r,
            colors[cluster].g,
            colors[cluster].b );
    }
    else {
        gfx_color(255, 255, 255);
    } 
    int px = (int)(round(x));
    int py = (int)(round(y));
    gfx_point(px,py);
}


void normalize_points(double **points, double **centroids, int K, int MAX_POINTS) {

    double maxX = -DBL_MAX;
    double minX = DBL_MAX;
    double maxY = -DBL_MAX;
    double minY = DBL_MAX;

    #pragma omp parallel for schedule(static) reduction(min:minX,minY) reduction(max:maxX,maxY)
    
    for (int i = 0; i < MAX_POINTS; i++){
        if (points[i][0] > maxX){
            maxX = points[i][0];
        }
        if (points[i][0] < minX){
            minX = points[i][0];
        }
        if (points[i][1] > maxY){
            maxY = points[i][1];
        }
        if (points[i][1] < minY){
            minY = points[i][1];
        }
    }
    

    #pragma omp parallel for
    for (int i = 0; i < MAX_POINTS; i++){
        points[i][0] = (points[i][0] - minX)*(XSIZE / (maxX - minX)); // linearly scale X to XSIZE
        points[i][1] = (points[i][1] - minY)*(YSIZE / (maxY - minY)); // linearly scale Y to YSIZE
        if (i < K){
            centroids[i][0] = (centroids[i][0] - minX)*(XSIZE / (maxX - minX)); // linearly scale X to XSIZE
            centroids[i][1] = (centroids[i][1] - minY)*(YSIZE / (maxY - minY)); // linearly scale Y to YSIZE
        }
    }
    

}*/

int main(int argc, char* argv[])
{
    double **points;
    double tstart, tstop;
    double **centroids;
    u_int8_t *clusters;

    int MAX_POINTS = 20000;
    int K = 5;
    if (argc >= 3 && argc <= 5){
        MAX_POINTS = atoi(argv[1]);
        K = atoi(argv[2]);
        if (strcmp(argv[3], "weak") == 0){
            int cores = atoi(argv[4]);
            MAX_POINTS = (int)round(sqrt(cores)*MAX_POINTS);
            K = (int)round(sqrt(cores)*K);
            printf("Samples: %d, Clusters: %d\n", MAX_POINTS, K);
        }
    }


    else{
        printf("Wrong number of arguments.");
        exit(1);
    }
    /* allocate the array */
    points = malloc(MAX_POINTS * sizeof *points);
    for (int i=0; i<MAX_POINTS; i++)
    {
        points[i] = malloc(DIM * sizeof *points[i]);
    }

    read_data("data/kmeans.txt", points, MAX_POINTS);   

    centroids = malloc(K * sizeof *centroids);
    for (int i=0; i<K; i++)
    {
        centroids[i] = malloc(DIM * sizeof *centroids[i]);
    }

    clusters = malloc(MAX_POINTS * sizeof *clusters);
    
    tstart = omp_get_wtime();

    kmeans_lloyd(points, centroids, clusters, K, MAX_POINTS); 

    tstop = omp_get_wtime();

    double elapsed_time = tstop - tstart;

    /*
    normalize_points(points, centroids, K, MAX_POINTS);
    gfx_open(XSIZE, YSIZE, "KMeans");

    for (int i = 0; i < MAX_POINTS; i++){
        draw_point(points[i][0], points[i][1], clusters[i], 0);
        if (i < K){
            // draw centroid as bigger point
            //printf("Centroid %d: (%lf, %lf)\n", i, centroids[i][0], centroids[i][1]); 
            draw_point(centroids[i][0]+1, centroids[i][1], i, 1);
            draw_point(centroids[i][0], centroids[i][1], i, 1); // centroid index is cluster number
            draw_point(centroids[i][0], centroids[i][1]+1, i, 1);
            draw_point(centroids[i][0]-1, centroids[i][1], i, 1);
            draw_point(centroids[i][0], centroids[i][1]-1, i, 1);
            draw_point(centroids[i][0]-1, centroids[i][1]-1, i, 1);
            draw_point(centroids[i][0]+1, centroids[i][1]+1, i, 1);
            draw_point(centroids[i][0]+1, centroids[i][1]-1, i, 1);
            draw_point(centroids[i][0]-1, centroids[i][1]+1, i, 1);
        }
    }


    gfx_wait();*/
    for (int i = 0; i < MAX_POINTS; i++){
        free(points[i]);
    }
    free(points);
    for (int i = 0; i < K; i++){
        free(centroids[i]);
    }
    free(centroids);
    free(clusters);
    printf("%lf", elapsed_time);
    return 0;
}