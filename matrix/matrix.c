//Copy of lab 5 fastest order//
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>  // For gettimeofday()
#include <time.h>
#include <math.h>  // For fabs (absolute value)

#define EPSILON 1e-6  // Tolerance for comparing floating-point numbers

void multiplyMatricesOrder2(double **firstMatrix, double **secondMatrix, double **resultMatrix) {
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }
}

//Function to fill the matrix with random double precision values
void fillRandomMatrix(double **matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = (rand() % 100) / 10.0; // Random numbers in the range [0.0, 10.0]
        }
    }
}

// Function to measure elapsed time using gettimeofday
double measureElapsedTime(struct timeval *start, struct timeval *end) {
    return (double)(end->tv_sec - start->tv_sec) + (double)(end->tv_usec - start->tv_usec) / 1000000.0;
}

// Function to dynamically allocate a matrix
double** allocateMatrix() {
    double **matrix = (double **)malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (double *)malloc(N * sizeof(double));
    }
    return matrix;
}

// Function to free the dynamically allocated matrix
void freeMatrix(double **matrix) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    // Declare pointers to dynamically allocated matrices
    double **firstMatrix = allocateMatrix();
    double **secondMatrix = allocateMatrix();
    double **result1 = allocateMatrix();

    // Seed the random number generator
    srand(time(NULL));

    // Fill the matrices with random values
    fillRandomMatrix(firstMatrix);
    fillRandomMatrix(secondMatrix);

    // Declare timeval structs to measure time
    struct timeval start, end;

    // Measure time for the second order of multiplication
    gettimeofday(&start, NULL);
    multiplyMatricesOrder2(firstMatrix, secondMatrix, result1);
    gettimeofday(&end, NULL);
    printf("Time taken for Order 2: %lf seconds\n", measureElapsedTime(&start, &end));

    // Free dynamically allocated memory
    freeMatrix(firstMatrix);
    freeMatrix(secondMatrix);
    freeMatrix(result1);

    return 0;
}