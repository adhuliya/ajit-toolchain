/* Factored discrete Fourier transform, or FFT, and its inverse iFFT */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread_channel.h>
#include <data_structs.h>

ThreadChannel tc;

xfftArgs fft_args;
xtwiddleArgs twiddle_args;

void twiddle_factors(int inv_flag, int start_index, int stride, complex* v, complex* vo, complex* ve, int n)
{
    int m;
    complex w, z;
    for(m=start_index; m<n/2; m += stride) {
	    if(inv_flag)
	    {
		    w.Re = cos(2*PI*m/(double)n);
		    w.Im = sin(2*PI*m/(double)n);
		    z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;	/* Re(w*vo[m]) */
		    z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;	/* Im(w*vo[m]) */
	    }
	    else
	    {
		    w.Re = cos(2*PI*m/(double)n);
		    w.Im = -sin(2*PI*m/(double)n);
		    z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;	/* Re(w*vo[m]) */
		    z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;	/* Im(w*vo[m]) */
	    }
	    v[  m  ].Re = ve[m].Re + z.Re;
	    v[  m  ].Im = ve[m].Im + z.Im;
	    v[m+n/2].Re = ve[m].Re - z.Re;
	    v[m+n/2].Im = ve[m].Im - z.Im;
    }
}


void
fft_top(complex* v, int N, complex* tmp)
{
    int k,m;    complex z, w, *vo, *ve;
    ve = tmp; vo = tmp+n/2;
    for(k=0; k<n/2; k++) {
      ve[k] = v[2*k];
      vo[k] = v[2*k+1];
    }

    // fft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
    setXfftArgs(&fft_args, n/2, ve, tmp);
    scheduleChannelJob(&tc, (void*) fft_thread, &fft_args);

    // local execution..
    fft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */


    void* vptr = MULL;
    while(getChannelResponse(&tc, &vptr))
    {
    }

    // on sidekick
    setXtwiddleArgs(&twiddle_args, 
			0,
			n,
			0,
			2,
			v, vo, ve);
    scheduleChannelJob(&tc, (void*) twiddle_factors_thread, &twiddle_args);

    // locally.
    twiddle_factors(0, 1,2,v,vo,ve, n);

    vptr = NULL;
    while(getChannelResponse(&tc, &vptr))
    {
    }

}




/* 
   fft(v,N):
   [0] If N==1 then return.
   [1] For k = 0 to N/2-1, let ve[k] = v[2*k]
   [2] Compute fft(ve, N/2);
   [3] For k = 0 to N/2-1, let vo[k] = v[2*k+1]
   [4] Compute fft(vo, N/2);
   [5] For m = 0 to N/2-1, do [6] through [9]
   [6]   Let w.re = cos(2*PI*m/N)
   [7]   Let w.im = -sin(2*PI*m/N)
   [8]   Let v[m] = ve[m] + w*vo[m]
   [9]   Let v[m+N/2] = ve[m] - w*vo[m]
   */
	void
fft( complex *v, int n, complex *tmp )
{
	if(n>1) {			/* otherwise, do nothing and return */
		int k,m;    complex z, w, *vo, *ve;
		ve = tmp; vo = tmp+n/2;
		for(k=0; k<n/2; k++) {
			ve[k] = v[2*k];
			vo[k] = v[2*k+1];
		}
		fft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
		fft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */

		twiddle_factors(0,0,1,v, vo,ve, n);
	}
	return;
}

/* 
   ifft(v,N):
   [0] If N==1 then return.
   [1] For k = 0 to N/2-1, let ve[k] = v[2*k]
   [2] Compute ifft(ve, N/2);
   [3] For k = 0 to N/2-1, let vo[k] = v[2*k+1]
   [4] Compute ifft(vo, N/2);
   [5] For m = 0 to N/2-1, do [6] through [9]
   [6]   Let w.re = cos(2*PI*m/N)
   [7]   Let w.im = sin(2*PI*m/N)
   [8]   Let v[m] = ve[m] + w*vo[m]
   [9]   Let v[m+N/2] = ve[m] - w*vo[m]
   */
	void
ifft( complex *v, int n, complex *tmp )
{
	if(n>1) {			/* otherwise, do nothing and return */
		int k,m;    complex z, w, *vo, *ve;
		ve = tmp; vo = tmp+n/2;
		for(k=0; k<n/2; k++) {
			ve[k] = v[2*k];
			vo[k] = v[2*k+1];
		}
		ifft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
		ifft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */

		twiddle_factors(1,0,1,v,vo,ve,n);
	}
	return;
}

void
ifft_top( complex *v, int n, complex *tmp )
{
    int k,m;    complex z, w, *vo, *ve;
    ve = tmp; vo = tmp+n/2;
    for(k=0; k<n/2; k++) {
      ve[k] = v[2*k];
      vo[k] = v[2*k+1];
    }

    // ifft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
    setXfftArgs(&fft_args, n/2, ve, tmp);
    scheduleChannelJob(&tc, (void*) ifft_thread, &fft_args);

    ifft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */

    void* vptr = MULL;
    while(getChannelResponse(&tc, &vptr))
    {
    }

    // on sidekick
    setXtwiddleArgs(&twiddle_args, 
			1,
			n,
			0,
			2,
			v, vo, ve);
    scheduleChannelJob(&tc, (void*) twiddle_factors_thread, &twiddle_args);
    twiddle_factors(1, 1,2,v,vo,ve,n);


    vptr = NULL;
    while(getChannelResponse(&tc, &vptr))
    {
    }
}


void setup()
{
	__ajit_serial_configure__(1,0,0);
	__ajit_serial_set_baudrate__ (115200, 80000000);
	__ajit_serial_set_uart_reset__ (0);

	CORTOS_DEBUG("Init channel.\n");
	// initialize scoreboard.
	initChannel(&tc, 1);
}

int main_00(void)
{
	complex v[N], v1[N], scratch[N];
	int k;

	/* Fill v[] with a function of known FFT: */
	for(k=0; k<N; k++) {
		v[k].Re = 0.125*cos(2*PI*k/(double)N);
		v[k].Im = 0.125*sin(2*PI*k/(double)N);
		v1[k].Re =  0.3*cos(2*PI*k/(double)N);
		v1[k].Im = -0.3*sin(2*PI*k/(double)N);
	}

	/* FFT, iFFT of v[]: */
	print_vector("Orig", v, N);
	uint64_t t0 =__ajit_get_clock_time();
	fft_top( v, N, scratch );
	uint64_t t1 =__ajit_get_clock_time();
	print_vector(" FFT", v, N);
	uint64_t t2 =__ajit_get_clock_time();
	ifft_top( v, N, scratch );
	uint64_t t3 =__ajit_get_clock_time();
	print_vector("iFFT", v, N);

	/* FFT, iFFT of v1[]: */
	print_vector("Orig", v1, N);
	uint64_t t4 =__ajit_get_clock_time();
	fft_top( v1, N, scratch );
	uint64_t t5 =__ajit_get_clock_time();
	print_vector(" FFT", v1, N);
	uint64_t t6 =__ajit_get_clock_time();
	ifft_top( v1, N, scratch );
	uint64_t t7 =__ajit_get_clock_time();
	print_vector("iFFT", v1, N);

	cortos_printf("Times: %f %f %f %f\n",
			 (double) (t1 - t0),
			 (double) (t3 - t2),
			 (double) (t5 - t4),
			 (double) (t7 - t6));
			
	exit(EXIT_SUCCESS);
}

int main_01 (void)
{
	void (*__fn) (void*);
	void *__arg;

	while(1) 
	{
		while(getChannelJob(&tc, (void**) &__fn, (void**) &__arg))
		{
		}

		(*__fn)(__arg);
		tc.status = CH_COMPLETED;
	}

}

