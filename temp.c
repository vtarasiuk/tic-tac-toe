#include <stdio.h>
#include <math.h>

static float calculateVariance(float *values, const int length);

int main() {
    // Example usage:
    float values[] = {78.0, 73.0, 73.5, 68.0, 75.0, 76.0, 80.0, 82.5, 78.5, 77.5};
    
    const int length = sizeof(values) / sizeof(float);
    float variance = calculateVariance(values, length);
    printf("Variance: %f\n", variance);

    return 0;
}

float calculateVariance(float *values, const int length) {
    printf("Length: %d\n", length);

    // Calculate the mean
    float mean = 0;
    for (int i = 0; i < length; i++) {
        mean += values[i];
    }
    mean /= length;
    printf("Mean: %f\n", mean);

    // Calculate the square of differences from the mean for each value
    float deviations[length];
    for (int i = 0; i < length; i++) {
        deviations[i] = pow(values[i] - mean, 2);
    }

    // Calculate the mean of squared deviations
    float meanDeviations = 0;
    for (int i = 0; i < length; i++) {
        meanDeviations += deviations[i];
    }
    meanDeviations /= (length - 1);

    return meanDeviations;
}