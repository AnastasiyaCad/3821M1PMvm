#include "CreateMatrix.h"

void CreateMatrix(int* matrix, int row, int cols) {
	for (int i = 0; i < row * cols; i++) {
		matrix[i] = i;
	}
}

void CreateMatrixRes(int* matrix, int row, int cols) {
	for (int i = 0; i < row * cols; i++) {
		matrix[i] = 0;
	}
}

void PrintMAtrix(int* matrix, int row, int cols) {
	for (int i = 0; i < row * cols; i++) {
		std::cout << matrix[i] << " ";
	}
	std::cout << std::endl;
}

bool TestComparisonMatrix(int* matrix1, int row1, int cols1, int* matrix2, int row2, int cols2) {
	try
	{
		if ((cols1 != cols2) && (row1 != row2)) {
			throw 123;
		}
		for (int i = 0; i < row1 * cols1; ++i) {
			if (matrix1[i] != matrix2[i]) {
				return false;
			}
		}
		return true;
	}
	catch (int i) {
		std::cout << "Error! Matrix sizes do not match" << std::endl;
	}
}
