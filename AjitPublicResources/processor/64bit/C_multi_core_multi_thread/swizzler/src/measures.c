// measures.c
//
// Contains the function defining the measures for randomness 
//
// AUTHOR : Manan Garg

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include <complex.h>
#include "measures.h"

// Expects 2 inputs as file names which will contain the main 
// file (inp1) and the reference file (inp2). The rest 3 inputs 
// are pointers which will store the values of the measures
void measure (const char* inp1, const char* inp2, double* measure1, double* measure2, int* measure3){

	FILE *file1 = fopen(inp1, "r");
    FILE *file2 = fopen(inp2, "r");

    if (!file1 || !file2) {
        perror("Error opening files, Make sure base.txt exists beforehand. Base file is the reference trace file against which comparison will be done. Please refer to the README file, measures section. If you dont want this comparison then create a base.txt in same directory as the script with just 0 in the first line. If you have a reference text file then please provide it as base.txt in same directory as scripts ");
        if (file1) fclose(file1);
        if (file2) fclose(file2);
        exit(1);
    }

    // variables for the number of lines of data present and the actual data present
    size_t size1 = 0, size2 = 0;
    double *data1 = NULL, *data2 = NULL;
    char line[256];
	
	// populates size1 and data1 by reading the first file
    while (fgets(line, sizeof(line), file1)) {
        data1 = realloc(data1, (size1 + 1) * sizeof(double));
        if (!data1) {
            perror("Memory allocation error");
            fclose(file1);
            fclose(file2);
            return ;
        }
        // Convert hex to decimal
        data1[size1++] = strtoul(line, NULL, 16); 
    }

    // Read the second file similarly
    while (fgets(line, sizeof(line), file2)) {
        data2 = realloc(data2, (size2 + 1) * sizeof(double));
        if (!data2) {
            perror("Memory allocation error");
            free(data1);
            fclose(file1);
            fclose(file2);
            return ;
        }
        // Convert hex to decimal
        data2[size2++] = strtoul(line, NULL, 16); 
    }

    fclose(file1);
    fclose(file2);
    
    // Makes the 2 sizes equal if they are not by appending zeroes
    if (size1 != size2) {
        int max_samples = (size1 > size2) ? size1 : size2;
		
		// calloc ensures the appending of zeroes
        double* new_data1 = calloc(max_samples, sizeof(double));
        double* new_data2 = calloc(max_samples, sizeof(double));

        if (!new_data1 || !new_data2) {
            free(data1);
            free(data2);
            free(new_data1);
            free(new_data2);
            return ;
        }

        // Copy original data to new arrays and pad with zeroes
        for (size_t i = 0; i < size1; i++) {
            new_data1[i] = data1[i];
        }
        for (size_t i = 0; i < size2; i++) {
            new_data2[i] = data2[i];
        }

        // Replace old arrays with resized ones
        free(data1);
        free(data2);
        data1 = new_data1;
        data2 = new_data2;
        size1 = size2 = max_samples;
    }
    
    // Calculates the mean of both the datas (Req for zero centering the data)
    // and also the number of similar entries for measure 3
    double mean1 = 0.0, mean2 = 0.0;
    int similar = 0;
    for (size_t i = 0; i < size1; i++) {
        mean1 += data1[i];
        mean2 += data2[i];
        
        if( data1[i] == data2[i] ){
    		similar++ ;
    	}
    	
    }
    mean1 /= size1;
    mean2 /= size2;

    // Subtract means (zero-centering the data)
    for (size_t i = 0; i < size1; i++) {
        data1[i] -= mean1;
        data2[i] -= mean2;
    }
    
    // Measure 3 is assigned over here
    *measure3 = similar;
    
    // Variables for cross and self correlations 
    double max_cross_corr = 0.0;
    double norm1 = 0.0, norm2 = 0.0;
    double max_self_corr = 0.0;
    double norm_self = 0.0;

    // Compute the normalization factor (energy of the signals)
    for (size_t i = 0; i < size1; i++) {
        norm1 += data1[i] * data1[i];
        norm2 += data2[i] * data2[i];
    }
    norm1 = sqrt(norm1);
    norm2 = sqrt(norm2);
    
    // Compute the normalised self(auto) and cross correlation
    for (size_t lag = 0; lag < size1; lag++) {
        double sum_cross = 0.0;
        double sum_self = 0.0;
        for (size_t i = 0; i < size1 - lag; i++) {
        	sum_self += data1[i] * data1[i + lag];
            sum_cross += data1[i] * data2[i + lag];
        }
        
        // Taking lag0 as the normalising factor for self correlation
        if (lag == 0){
        	norm_self = sum_self;
        }
        // Finding the maximum auto correlation to report as final measure1
        if ((lag != 0) && (sum_self > max_self_corr)) {
            max_self_corr = sum_self;
        }
        // Finding the maximum cross correlation to report as final measure2
        if (sum_cross > max_cross_corr) {
            max_cross_corr = sum_cross;
        }
    }
    
    // Normalising the self(auto) and cross correlation
    max_self_corr /= norm_self;
    max_cross_corr /= (norm1*norm2);
    
    // Assigning the proper pointers
    *measure2 = max_cross_corr;
    *measure1 = max_self_corr;
    
    free (data1);
    free (data2);
    
    return ;
}
