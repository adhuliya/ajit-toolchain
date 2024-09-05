/* Factored discrete Fourier transform, or FFT, and its inverse iFFT */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef USE_CORTOS
#include <cortos.h>
#endif
#include <data_structs.h>
void setXfftArgs (xfftArgs* args, int n, complex* v, complex* tmp)
{
	args->n = n;
	args->v = v;
	args->tmp = tmp;
}

void setXtwiddleArgs (xtwiddleFactorArgs* args, 
			int inv_flag,
			int n,
			int start_index,
			int stride,
			complex* v,
			complex* vo,
			complex* ve)
{
	args->inv_flag = inv_flag;
	args->n = n;
	args->start_index = start_index;
	args->stride = stride;
	args->v = v;
	args->vo = vo;
	args->ve = ve;
}

void twiddle_factors_thread (void *vargs)
{
	xtwiddleFactorArgs* args = (xtwiddleFactorArgs*) vargs;
	twiddle_factors (args->inv_flag,
				args->start_index,
				args->stride,
				args->v,
				args->vo,
				args->ve,
				args->n);
}
		
/* Print a vector of complexes as ordered pairs. */
void
print_vector(
	     const char *title,
	     complex *x,
	     int n)
{
  int i;
  PRINTF("%s (dim=%d):", title, n);
  for(i=0; i<n; i++ ) 
	PRINTF(" %5.2f,%5.2f ", x[i].Re,x[i].Im);
  PRINTF("\n");
  return;
}

void fft_thread (void* vargs)
{
    int n = ((xfftArgs*)vargs)->n;
    complex* v = ((xfftArgs*)vargs)->v;
    complex* tmp = ((xfftArgs*)vargs)->tmp;
	
    CORTOS_DEBUG("calling fft(0x%x, %d, 0x%x.\n",
			(uint32_t) v, n, (uint32_t) tmp);
    fft(v,n,tmp);

}

void ifft_thread (void* vargs)
{
    int n = ((xfftArgs*)vargs)->n;
    complex* v = ((xfftArgs*)vargs)->v;
    complex* tmp = ((xfftArgs*)vargs)->tmp;
    CORTOS_DEBUG("calling ifft(0x%x, %d, 0x%x.\n",
			(uint32_t) v, n, (uint32_t) tmp);
    ifft(v,n,tmp);
}

