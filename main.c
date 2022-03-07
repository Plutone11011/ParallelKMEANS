/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/


#include <stdio.h>

#include "kmeans.h"
#include "utils.h"



int main()
{
    double data[MAX_POINTS][MAX_FEATURES] = {0.0} ;
    
    
    read_csv("data/housing.csv", data);   

    // the actual points used are 2d or 3d for lloyd (for now?)
    double points[MAX_POINTS][DIM]; 
    double centroids[K][DIM] = {0.0} ;
    for (int i = 0; i < MAX_POINTS; i++ ) {

        for (int j = 0; j < DIM; j++) {
            points[i][j] = data[i][j+LAT]; 
        }
    }

    kmeans_lloyd(points, centroids);

    return 0;
}