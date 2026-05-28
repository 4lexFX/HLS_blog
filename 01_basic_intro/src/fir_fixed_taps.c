
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "fir_fixed_taps.h"


// Static coefficient array (pre-configured)
const int32_t FIR_COEFFS[MAX_FILTER_ORDER] = {
    // 21-tap band-pass filter coefficients (scaled by 1000 for integer math)
    12,  36,  85, 158, 245, 329, 393, 421, 402, 336,
    236, 121,   8, -89,-160,-198,-202,-176,-129, -70,
    -12,
    // Pad with zeros to MAX_FILTER_ORDER
    #if MAX_FILTER_ORDER > 21
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    #endif
};


// FIR filter function (to be synthesized)
void fir_fixed_taps(
    int32_t input[TEST_INPUT_SIZE],
    int32_t output[TEST_INPUT_SIZE],
    int input_len,
    int filter_taps
) {
    int output_len = input_len - filter_taps + 1;
    
    OUTPUT_LOOP: for (int n = 0; n < output_len; n++) {
        int32_t sum = 0;  
        
        TAPS_LOOP: for (int k = 0; k < filter_taps; k++) {
            sum += FIR_COEFFS[k] * input[n + k];
        }
        
        output[n] = sum; 
    }
}
