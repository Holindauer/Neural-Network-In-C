#include "libraries.h"
#include "functions.h"
#include "structs.h"


//-------------------------------------------------------------------------------------------------------------------------<Weight Initialization>

// Function to generate a random float between two given values
double random_double(double min, double max) {
    return (max - min) * ((double)rand() / RAND_MAX) + min;
}

/*
    Function to randomly initialize a weight matrix using He initialization.
    He initialization is useful for mitigating the vanishing/exploding grad
    problem. The goal is to keep the variance of activation function outputs
    roughly the same.

    For context, weight matricies have the shape [num_neurons, input_features]

    Weights are initialze from a normal distribution with a mean of 0 and a std
    of sqrt( 2 / input_features )
*/
void he_initialize(double* matrix, int rows, int cols) {
    double stddev = sqrt(2.0 / cols);                                // get standard deviation for He initialization

    for (int i = 0; i < rows; i++) {                                // loop through matrix elements
        for (int j = 0; j < cols; j++) {

            // Box-Muller transform to approximate random numbers 

            double u1 = random_double(0.0, 1.0);                      // generate the numbers u1 and u2 
            double u2 = random_double(0.0, 1.0);                      // a from uniform distribution

            double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2); // use u1 and u2 to compute z0 from 
            // the standard normal distribution
            // Assign the weight
            matrix[INDEX(i, j, cols)] = stddev * z0;                // multiply z0 by std to transform 
            // z0 into the correct distribution

        }
    }
}
