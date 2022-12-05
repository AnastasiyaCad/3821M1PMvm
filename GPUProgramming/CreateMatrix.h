#pragma once

#include <iostream>
#include <omp.h>

void PrintMAtrix(int* matrix, int row, int cols);
void CreateMatrix(int* matrix, int row, int cols);
void CreateMatrixRes(int* matrix, int row, int cols);
bool TestComparisonMatrix(int* matrix1, int row1, int cols1, int* matrix2, int row2, int cols2);
