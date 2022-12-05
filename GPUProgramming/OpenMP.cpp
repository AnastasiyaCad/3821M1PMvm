#include "OpenMP.h"

double openmp_multiply_matrix_serial(int* matrixA, int* matrixB, int* resultMatrix, int rowA, int colsA, int rowB, int colsB) {
    int threadsNum = 1;
    omp_set_num_threads(threadsNum);
    int i, j, k;

    double start = omp_get_wtime();

#pragma omp parallel for shared(matrixA, matrixB, resultMatrix) private(i, j, k)
    for (i = 0; i < rowA; ++i) {
        for (j = 0; j < colsB; ++j) {
            for (k = 0; k < colsA; ++k) {
                resultMatrix[i * colsB + j] += matrixA[i * colsA + k] * matrixB[k * colsB + j];
            }
        }
    }
    double end = omp_get_wtime();
    double res_time = end - start;
    return res_time;
}

double openmp_multiply_matrix_parallel(int* matrixA, int* matrixB, int* resultMatrix, int rowA, int colsA, int rowB, int colsB) {

    int threadsNum = 4;
    omp_set_num_threads(threadsNum);
    int i, j, k;

    double start = omp_get_wtime();
#pragma omp parallel for shared(matrixA, matrixB, resultMatrix) private(i, j, k)
    for (i = 0; i < rowA; ++i) {
        for (j = 0; j < colsB; ++j) {
            for (k = 0; k < colsA; ++k) {
                resultMatrix[i * colsB + j] += matrixA[i * colsA + k] * matrixB[k * colsB + j];
            }
        }
    }
    double end = omp_get_wtime();
    double res_time = end - start;
    return res_time;
}
