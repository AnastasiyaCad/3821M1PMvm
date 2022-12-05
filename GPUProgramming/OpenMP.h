#pragma once

#include "CreateMatrix.h"

double openmp_multiply_matrix_serial(int* matrixA, int* matrixB, int* resultMatrix, int rowA, int colsA, int rowB, int colsB);
double openmp_multiply_matrix_parallel(int* matrixA, int* matrixB, int* resultMatrix, int rowA, int colsA, int rowB, int colsB);