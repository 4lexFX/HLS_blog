#ifndef FIR_FIXED_TAPS_H
#define FIR_FIXED_TAPS_H

#include <stdint.h>

#define MAX_FILTER_ORDER 128
#define TEST_INPUT_SIZE 100
#define TEST_TAPS 21
#define EPSILON 1e-3  // Tolerance for floating-point comparisons

extern const int32_t FIR_COEFFS[];

void fir_fixed_taps( int32_t input[], int32_t output[], int input_len, int filter_taps);

#endif 
