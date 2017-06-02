/**
 * Document: MaxCompiler Tutorial (maxcompiler-tutorial)
 * Chapter: 3      Example: 3      Name: Moving Average Weighted
 * MaxFile name: MovingAverageWeighted
 * Summary:
 *   CPU code for the three point moving average design.
 */
#include "Maxfiles.h" 			// Includes .max files
#include <MaxSLiCInterface.h>	// Simple Live CPU interface

float X[16] = { 1, 1,
                1, 3,
                5, 3,
                8, 4,
                1, 3,
                9, 4,
                10,2,
                1, 8
};
float Y[8] = { 0, 1, 0, 0, 1, 1, 0, 1 };
float W1_vec[8];
float W2_vec[8];
float B_vec[8];

int main()
{
    float W1 = 0;
    float W2 = 0;
    float B = 0;

	printf("Running DFE\n");
	// Train multiple epochs with CPU loop
	// TODO: move this loop also to DataFlow
    for (int j = 0; j < 10; ++j) {
        // Train on entire batch of data
    	float weights[] = {W1, W2, B};
    	MovingAverageWeighted_weighted(4, weights, X, Y, W1_vec, W2_vec, B_vec);
    	
    	
    	// Fold results on CPU
    	float W1sum = 0;
    	float W2sum = 0;
    	float Bsum = 0;
    
        for (int i = 0; i < 8; ++i) {
    	   // printf("W[%d] = %f\n", i, W_vec[i]);
    	    W1sum += W1_vec[i];
    	    W2sum += W2_vec[i];
    	    Bsum += B_vec[i];
        }
        
        W1 = W1sum / 8.0;
        W2 = W2sum / 8.0;
        B = Bsum / 8.0;
        
        
        // Check error on CPU
        float avg_err = 0;
        for (int i = 0; i < 8; ++i) {
            float err = pow(exp(W1*X[2*i] + W2*X[2*i + 1] + B) - Y[i], 2.0);
            avg_err += err;
        }
        
        printf("AvgErr = %f\n", avg_err / 8.0);
    }
    
	return 0;
}

/* CPU training loop
float w1sum = 0;
float w2sum = 0;
float bsum = 0;
for (int i = 0; i < samples; ++i) {
    float p = exp(w1*x[2*i] + w2*x[2*i+1] + b);
    float err = p - y[i];
    w1sum += w1 - 0.01 * x[2*i] * err;
    w2sum += w2 - 0.01 * x[2*i+1] * err;
    bsum += b - 0.01 * err;
}
*/
