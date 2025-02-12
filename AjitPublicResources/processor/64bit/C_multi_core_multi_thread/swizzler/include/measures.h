#include <stdint.h>
#include <stdio.h>

#ifndef measures_h___
#define  measures_h___

// Expects 2 inputs as file names which will contain the main 
// file (inp1) and the reference file (inp2). The rest 3 inputs 
// are pointers which will store the values of the measures
void measure (const char* inp1, const char* inp2, double* measure1, double* measure2, int* measure3);
#endif
