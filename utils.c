#include "utils.h"


void read_data(char *filename, double data[MAX_POINTS][MAX_FEATURES]){

    FILE *fp=fopen(filename,"r");
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size ;

    getline(&line_buf, &line_buf_size, fp); // skip first line with column names
    
    double number;
    for (int i = 0; i < MAX_POINTS; i++){

        line_size = getline(&line_buf, &line_buf_size, fp);
        
        for (int j = 0; j < MAX_FEATURES; j++){
            number = strtod(line_buf, &line_buf);
            
            if (j < MAX_FEATURES - 1){
                line_buf++; // skip comma
            }
            
            data[i][j] = number; 
        }
        // need to reinitialize line_buf at the end of inner loop
        // to avoid memory leak
        line_buf = NULL; 
        line_buf_size = 0;
        
    }

    fclose(fp);
    
}