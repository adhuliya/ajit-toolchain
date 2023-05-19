#ifndef data_structs_h____
#define data_structs_h____

#define q	12		/* for 2^12 points */
#define N	(1<<q)		/* N-point FFT, iFFT */

typedef float real;
typedef struct{real Re; real Im;} complex;

#ifndef PI
# define PI	3.14159265358979323846264338327950288
#endif

#ifdef USE_CORTOS
#define PRINTF cortos_printf
#else
#define PRINTF ee_printf
#endif


typedef struct xfftArgs__ {
	int n;
	complex* v;
	complex* tmp;
} xfftArgs;


typedef struct xtwiddleFactorArgs {
	int inv_flag;
	int n;
	int start_index;
	int stride;
	complex* v;
	complex* vo;
	complex* ve;
} xtwiddleFactorArgs;


void fft( complex *v, int n, complex *tmp );
void ifft( complex *v, int n, complex *tmp );
void twiddle_factors(int inv_flag, int start_index, int stride, complex* v, complex* vo, complex* ve, int n);
void setXfftArgs (xfftArgs* args, int n, complex* v, complex* tmp);
void setXtwiddleArgs (xtwiddleFactorArgs* args, 
			int inv_flag,
			int n,
			int start_index,
			int stride,
			complex* v,
			complex* vo,
			complex* ve);
void twiddle_factors_thread (void *vargs);
void fft_thread (void* args);
void ifft_thread (void* args);

void print_vector(
	     const char *title,
	     complex *x,
	     int n);
#endif

