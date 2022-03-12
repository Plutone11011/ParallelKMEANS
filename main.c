/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/


#include <stdio.h>
#include <math.h>
#include <float.h>
#include "kmeans.h"
#include "utils.h"
#include "gfx.h"


//const int XSIZE = 800, YSIZE = 600; 
const int XSIZE = 1024, YSIZE = 768;

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

void draw_point(double x, double y, u_int8_t cluster){
        
    gfx_color(colors[cluster].r,
            colors[cluster].g,
            colors[cluster].b );            
    int px = (int)(round(x));
    int py = (int)(round(y));
    printf("Point to draw: %d, %d\n", px, py);
    gfx_point(px,py);
}


void normalize_points(double points[MAX_POINTS][DIM], double centroids[K][DIM]) {

    double maxX = -DBL_MAX;
    double minX = DBL_MAX;
    double maxY = -DBL_MAX;
    double minY = DBL_MAX;

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


    for (int i = 0; i < MAX_POINTS; i++){
        points[i][0] = (points[i][0] - minX)*(XSIZE / (maxX - minX)); // linearly scale X to XSIZE
        points[i][1] = (points[i][1] - minY)*(YSIZE / (maxY - minY)); // linearly scale Y to YSIZE
        if (i < K){
            centroids[i][0] = (centroids[i][0] - minX)*(XSIZE / (maxX - minX)); // linearly scale X to XSIZE
            centroids[i][1] = (centroids[i][1] - minY)*(YSIZE / (maxY - minY)); // linearly scale Y to YSIZE
        }
    }
    

}

int main()
{
    //double data[MAX_POINTS][MAX_FEATURES] = {0.0} ;
    srand(time(NULL));

    
    //read_csv("data/housing.csv", data);   

    // the actual points used are 2d or 3d for lloyd (for now?)
    double points[MAX_POINTS][DIM]; 
    double centroids[K][DIM] = {0.0} ;
    for (int i = 0; i < MAX_POINTS; i++ ) {
        points[i][0] = (double)(rand() % XSIZE);
        points[i][1] = (double)(rand() % YSIZE);
    }
    u_int8_t clusters[MAX_POINTS] = {0};
    kmeans_lloyd(points, centroids, clusters);

    normalize_points(points, centroids);

    gfx_open(XSIZE, YSIZE, "KMeans");

    for (int i = 0; i < MAX_POINTS; i++){
        draw_point(points[i][0], points[i][1], clusters[i]);
        if (i < K){
            draw_point(centroids[i][0], centroids[i][1], i); // centroid index is cluster number
        }
    }


    gfx_wait();
    return 0;
}