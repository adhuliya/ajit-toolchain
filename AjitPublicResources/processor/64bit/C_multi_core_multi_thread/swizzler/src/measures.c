#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include <fftw3.h>
#include <complex.h>

FILE* input_file = NULL;

// Function to calculate the log2 of an integer
int log2_int(int N) {
    int k = N, i = 0;
    while (k) {
        k >>= 1;
        i++;
    }
    return i - 1;
}

// Function to check if the number of elements is a power of 2
int check(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

// Function to calculate the reverse of a number
int reverse(int N, int n) {
    int j, p = 0;
    for (j = 1; j <= log2_int(N); j++) {
        if (n & (1 << (log2_int(N) - j)))
            p |= 1 << (j - 1);
    }
    return p;
}

// Function to reorder the array based on reverse order
void ordina(double complex* f1, int N) {
    double complex *f2 = (double complex *)malloc(N * sizeof(double complex));
    // Check if malloc was successful
    if (f2 == NULL) {
        printf("Memory allocation failed!\n");
        return;  // Exit if memory allocation failed
    }
    for (int i = 0; i < N; i++)
        f2[i] = f1[reverse(N, i)];
    for (int j = 0; j < N; j++)
        f1[j] = f2[j];
    free(f2);
}

// Function to perform the FFT transformation
void transform(double complex* f, int N) {
    ordina(f, N);  // Reverse order
    //printf("Milestone 1.91\n");
    double complex* W;
    W = (double complex*)malloc(N / 2 * sizeof(double complex));
    W[0] = 1.0 + 0.0 * I;
    W[1] = cexp(-2.0 * M_PI * I / N);  // Polar representation
    for (int i = 2; i < N / 2; i++)
        W[i] = cpow(W[1], i);
    
    int n = 1;
    int a = N / 2;
    for (int j = 0; j < log2_int(N); j++) {
        for (int i = 0; i < N; i++) {
            if (!(i & n)) {
                double complex temp = f[i];
                double complex Temp = W[(i * a) % (n * a)] * f[i + n];
                f[i] = temp + Temp;
                f[i + n] = temp - Temp;
            }
        }
        n *= 2;
        a = a / 2;
    }
    free(W);
}

// Function to compute the FFT of a sequence and multiply by a constant factor
void FFT(double complex* f, int N, double d) {
    transform(f, N);
    for (int i = 0; i < N; i++)
        f[i] *= d;  // Multiply by the step size
}

// Function to compute magnitudes from a file1 containing hexadecimal numbers
double* compute_magnitude(const char* filename, int* num_samples_out) {
    FILE* file1 = fopen(filename, "r");
    if (!file1) {
        perror("Error opening file1");
        return NULL;
    }

    //printf("Milestone 1.6\n");

	int num_samples = 0;
	uint32_t temp;
	while (fscanf(file1, "%X", &temp) == 1) {
	    num_samples++;
	}
	uint32_t* signal = (uint32_t*)malloc(num_samples * sizeof(uint32_t));
	if (!signal) {
	    perror("Memory allocation failed");
	    fclose(file1);
	    return NULL;
	}
	rewind(file1);
	int index = 0;
	while (fscanf(file1, "%X", &temp) == 1) {
	    signal[index++] = temp;
	}

// Now `signal` contains the parsed data, and `num_samples` is the size of the array
	//printf("Milestone 1.65\n");
	//printf("num_samples: %d\n", num_samples);
    fclose(file1);
	//printf("Milestone 1.7\n");
    // Ensure the number of samples is a power of 2
    int N = 1;
    while (N < num_samples) {
        N *= 2;
    }
//printf("N : %d\n",N);
    // Pad the signal with zeros if necessary to make the size a power of 2
    signal = (uint32_t*)realloc(signal, N * sizeof(uint32_t));
    for (int i = num_samples; i < N; i++) {
        signal[i] = 0;
    }
//printf("Milestone 1.8\n");
    // Allocate FFT arrays
    double complex* vec = (double complex*)malloc(N * sizeof(double complex));
    for (int i = 0; i < N; i++) {
        vec[i] = (double complex)signal[i];
    }

    // Perform FFT
    double d = 1.0;  // Sampling step (could be passed as an argument if needed)
    //printf("Milestone 1.9\n");
    FFT(vec, N, d);
	//printf("Milestone 1.99\n");
    // Compute the magnitudes
    double* magnitudes = (double*)malloc(N * sizeof(double));
    for (int i = 1; i < N ; i++) {
        magnitudes[i-1] = cabs(vec[i]);  // Compute magnitude of complex number
    }

    free(signal);
    free(vec);

    *num_samples_out = N - 1;  // Return the size of the magnitude array
    return magnitudes;
}

double measure2(const char* inp1, const char* inp2) {
    if (!inp1 || !inp2) {
        perror("Invalid input files");
        return NAN;
    }

    // Compute magnitude spectrums for both files
    int num_samples1 = 0, num_samples2 = 0;
    double* magnitude1 = compute_magnitude(inp1, &num_samples1);
    double* magnitude2 = compute_magnitude(inp2, &num_samples2);

    if (!magnitude1 || !magnitude2) {
        free(magnitude1);
        free(magnitude2);
        return NAN;
    }

    // Ensure the number of samples matches
    if (num_samples1 != num_samples2) {
        fprintf(stderr, "Error: Magnitude spectra have different lengths\n");
        free(magnitude1);
        free(magnitude2);
        return NAN;
    }

    // Compute dot product for similarity score
    double dot_product = 0;
    for (int i = 0; i < num_samples1; i++) {
        dot_product += magnitude1[i] * magnitude2[i];
    }

    // Cleanup
    free(magnitude1);
    free(magnitude2);

    return dot_product;
}

double measure1(const char* inp) {
    if (!inp) {
        perror("Invalid input file1");
        return NAN;
    }
    // Compute magnitude spectrum for the file1
    int num_samples = 0;
    //printf("Milestone 1.5\n");
    double* magnitude = compute_magnitude(inp, &num_samples);
    if (!magnitude) {
        return NAN;
    }

    // Compute CV (coefficient of variation)
    double sum = 0, sum_sq = 0;
    for (int i = 0; i < num_samples; i++) {
        sum += magnitude[i];
        sum_sq += magnitude[i] * magnitude[i];
    }

    double mean = sum / num_samples;
    double variance = (sum_sq / num_samples) - (mean * mean);
    double std_dev = sqrt(variance);
    double cv = (mean != 0) ? (std_dev / mean) * 100 : NAN;
	//printf("Milestone 2\n");
    // Cleanup
    free(magnitude);

    return cv;
}

