#include "kmeans.h"

double dist2(double point1[], double point2[], int size){
    
    double res = 0;
    for (int i = 0; i < size; i++){
        printf("Distance between points (%lf, %lf)\n", point1[i], point2[2]);
        res += (point1[i] - point2[i])*(point1[i] - point2[i]);
    }
    
    return res;
    
}

void kmeans_lloyd(double data[MAX_POINTS][MAX_POINTS], u_int8_t k){
    
    // they could be equal, whatever
    /*int c1 = rand() % 16 ;
    int c2 = rand() % 16 ;
    int c3 = rand() % 16 ;
    for (int i = 0; i < k; i++){
        
    }*/
    
    // will return matrix of same size data of int
    // each cell containing cluster number
}