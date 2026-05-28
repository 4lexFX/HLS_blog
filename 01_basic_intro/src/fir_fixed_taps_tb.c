
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// DUT
#include "fir_fixed_taps.h"


// Golden reference implementation (floating-point for accuracy comparison)
void fir_golden_reference(
    double input[TEST_INPUT_SIZE],
    double output[TEST_INPUT_SIZE],
    int input_len,
    const double coeffs[MAX_FILTER_ORDER],
    int filter_taps
) {
    
    int output_len = input_len - filter_taps + 1;
    
    for (int n = 0; n < output_len; n++) {
        double sum = 0.0;
        for (int k = 0; k < filter_taps; k++) {
            sum += coeffs[k] * input[n + k];
        }
        output[n] = sum;
    }
}



// Test case: Step response test
int test_step_response(void) {
    printf("\n=== Test 2: Step Response ===\n");
    
    int input_len = TEST_INPUT_SIZE;
    int32_t input[input_len];
    int32_t output[input_len - TEST_TAPS + 1];
    
    // Create step signal (all ones)
    for (int i = 0; i < input_len; i++) {
        if ( i < (TEST_TAPS +1) ) {
            input[i] = 0;
        } else { 
            input[i] = 100;  // Step amplitude
        }
    }
    
    // Run FIR filter
    fir_fixed_taps(input, output, input_len, TEST_TAPS);
    
    // Calculate expected using golden reference (double precision)
    double input_double[input_len];
    double coeffs_double[TEST_TAPS];
    double expected[input_len - TEST_TAPS + 1];
    
    for (int i = 0; i < input_len; i++) {
        if ( i < (TEST_TAPS +1) ) {
            input_double[i] = 0.0;
        } else { 
            input_double[i] = 100.0;  // Same amplitude
        }
    }
    
    for (int i = 0; i < TEST_TAPS; i++) {
        coeffs_double[i] = FIR_COEFFS[i];
    }
    
    fir_golden_reference(input_double, expected, input_len, coeffs_double, TEST_TAPS);
    
    // Compare results
    int passed = 1;
    int output_len = input_len - TEST_TAPS + 1;
    
    printf("First 10 outputs (fixed vs floating reference):\n");
    for (int n = 0; n < 10 && n < output_len; n++) {
        int32_t diff = abs(output[n] - (int32_t)expected[n]);
        double rel_error = (expected[n] != 0) ? fabs(diff / expected[n]) : fabs(diff);
        
        printf("  output[%d] = %8d, expected = %8.1f, diff = %d", 
               n, output[n], expected[n], diff);
        
        if (diff > 2 || rel_error > 0.01) {  // Allow 0.1% error or 2 LSBs
            passed = 0;
            printf(" FAIL\n");
        } else {
            printf(" PASS\n");
        }
    }
    
    printf("Step response test: %s\n", passed ? "PASSED" : "FAILED");
    return passed;
}

// testbench framework
int main(void) {
    printf("========================================\n");
    printf("FIR FILTER SELF-CHECKING TESTBENCH\n");
    printf("========================================\n");
    printf("Filter configuration:\n");
    printf("  Max order: %d\n", MAX_FILTER_ORDER);
    printf("  Active taps: %d\n", TEST_TAPS);
    printf("  Coefficient type: int32_t (scaled by 1000 for fractional)\n");
    
    int all_tests_passed = 1;
    
    // Run all tests
    all_tests_passed &= test_step_response();
        
    // Final result
    printf("\n========================================\n");
    printf("TESTBENCH SUMMARY\n");
    printf("========================================\n");
    
    if (all_tests_passed) {
        printf("ALL TESTS PASSED!\n");
        return 0;
    } else {
        printf("SOME TESTS FAILED!\n");
        return 1;
    }
}


