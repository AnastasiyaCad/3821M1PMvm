#pragma once

double openclMatrix(int* matrixA, int* matrixB, int* matrixRes, int rowA, int colsA, int rowB, int colsB);
double opencl_multiply_matrix(int* matrixA, int* matrixB, int* matrixRes, int rowA, int colsA, int rowB, int colsB);
double opencl_multiply_matrix_optim(int* matrixA, int* matrixB, int* matrixRes, int rowA, int colsA, int rowB, int colsB);
