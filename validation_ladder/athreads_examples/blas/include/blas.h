#ifndef blas_h____
#define blas_h____

#define DOTPRODUCT   1
#define MATRIXVECTOR 2

//
// etc..
//
typedef blasThreadDataStructure__ {
	int operation;
	void *arg_1;
	void *arg_2;
	void *arg_3;
	void *arg_4;
	void *arg_5;
	void *arg_6;
	void *arg_7;
	void *arg_8;
} blasThreadData;

double blas_dotProduct (int N, double* a, double* b);
double blas_dotProduct_inner (int N, double* a, double* b);

#endif

