#include "Tests.h"

//bool Test1() {
//	int row1 = 3;
//	int cols1 = 3;
//	int* matrixA = new int[row1 * cols1];
//	CreateMatrix(matrixA, row1, cols1);
//
//	int row2 = 3;
//	int cols2 = 3;
//	int* matrixB = new int[row2 * cols2];
//	CreateMatrix(matrixB, row2, cols2);
//
//	int row3 = row1;
//	int cols3 = cols2;
//	int* matrixRes = new int[row3 * cols3];
//
//	int time = openmp_multiply_matrix_serial(matrixA, matrixB, matrixRes, cols3, cols3, row3, cols3);
//
//	int answer[9] = {
//						15,	18,	 21,
//						42,	54,	 66,
//						69,	90,	111
//	};
//
//
//	if (TestComparisonMatrix(matrixRes, row3, cols3, answer, row3, cols3)) {
//		return true;
//	}
//	else {
//		std::cout << "The Test 1 will fail!" << std::endl;
//			return false;
//	}
//}

bool Test1_2() {
	int row1 = 32;
	int cols1 = 32;
	int* matrixA = new int[row1 * cols1];

	for (int i = 0; i < row1 * cols1; i++) {
		matrixA[i] = i;
	}

	//CreateMatrix(matrixA, row1, cols1);

	//PrintMAtrix(matrixA, row1, cols1);

	int row2 = 32;
	int cols2 = 32;
	int* matrixB = new int[row2 * cols2];
	CreateMatrix(matrixB, row2, cols2);
	//PrintMAtrix(matrixB, row2, cols2);

	int row3 = row1;
	int cols3 = cols2;
	int* matrixRes1 = new int[row3 * cols3];
	CreateMatrixRes(matrixRes1, row3, cols3);
	int* matrixRes2 = new int[row3 * cols3];
	CreateMatrixRes(matrixRes2, row3, cols3);
	double timeomp = openmp_multiply_matrix_serial(matrixA, matrixB, matrixRes1, row1, cols1, row2, cols2);
	//std::cout << "CPU" << std::endl;
	//PrintMAtrix(matrixRes1, row3, cols3);
	double time = openclMatrix(matrixA, matrixB, matrixRes2, cols3, cols3, row3, cols3);
	//double time = opencl_multiply_matrix_optim(matrixA, matrixB, matrixRes2, row1, cols1, row2, cols2);
	//double time = opencl_multiply_matrix(matrixA, matrixB, matrixRes2, row1, cols1, row2, cols2);
	PrintMAtrix(matrixRes2, row3, cols3);
	//double time = opencl_multiply_matrix_optim(matrixA, matrixB, matrixRes, cols3, cols3, row3, cols3);


	if (TestComparisonMatrix(matrixRes2, row3, cols3, matrixRes1, row3, cols3)) {
		return true;
	}
	else {
		std::cout << "The Test 1_2 will fail!" << std::endl;
		return false;
	}
}


//bool Test2() {
//	int row1 = 3;
//	int cols1 = 3;
//	int* matrixA = new int[row1 * cols1];
//	CreateMatrix(matrixA, row1, cols1);
//
//	int row2 = 3;
//	int cols2 = 3;
//	int* matrixB = new int[row2 * cols2];
//	CreateMatrix(matrixB, row2, cols2);
//
//	int row3 = row1;
//	int cols3 = cols2;
//	int* matrixRes1 = new int[row3 * cols3];
//
//	int* matrixRes2 = new int[row3 * cols3];
//
//
//	double timeCPU = openmp_multiply_matrix_serial(matrixA, matrixB, matrixRes1, row3, cols3, row3, cols3);
//	double timeOMP = openmp_multiply_matrix_parallel(matrixA, matrixB, matrixRes2, row3, cols3, row3, cols3);
//
//	std::cout << std::endl;
//
//	if (TestComparisonMatrix(matrixRes1, row3, cols3, matrixRes2, row3, cols3)) {
//		return true;
//	}
//	else {
//		std::cout << "The Test 2 will fail!" << std::endl;
//		return false;
//	}
//}
//
//bool Test3() {
//	int row1 = 5;
//	int cols1 = 5;
//	int* matrixA = new int[row1 * cols1];
//	CreateMatrix(matrixA, row1, cols1);
//
//	int row2 = 3;
//	int cols2 = 3;
//	int* matrixB = new int[row2 * cols2];
//	CreateMatrix(matrixB, row2, cols2);
//
//	int row3 = row1;
//	int cols3 = cols2;
//	int* matrixRes1 = new int[row3 * cols3];
//
//	int* matrixRes2 = new int[row3 * cols3];
//
//	double timeCPU = openmp_multiply_matrix_serial(matrixA, matrixB, matrixRes1, row3, cols3, row3, cols3);
//	double timeGPUopt = opencl_multiply_matrix(matrixA, matrixB, matrixRes2, row3, cols3, row3, cols3);
//
//	if (TestComparisonMatrix(matrixRes1, row3, cols3, matrixRes1, row3, cols3)) {
//		return true;
//	}
//	else {
//		std::cout << "The Test 3 will fail!" << std::endl;
//		return false;
//	}
//}
//
//bool Test4() {
//	int row1 = 5;
//	int cols1 = 5;
//	int* matrixA = new int[row1 * cols1];
//	CreateMatrix(matrixA, row1, cols1);
//
//	int row2 = 5;
//	int cols2 = 5;
//	int* matrixB = new int[row2 * cols2];
//	CreateMatrix(matrixB, row2, cols2);
//
//	int row3 = row1;
//	int cols3 = cols2;
//	int* matrixRes1 = new int[row3 * cols3];
//
//	int* matrixRes2 = new int[row3 * cols3];
//
//	double timeCPU = openmp_multiply_matrix_serial(matrixA, matrixB, matrixRes1, row3, cols3, row3, cols3);
//	double timeGPUopt = opencl_multiply_matrix_optim(matrixA, matrixB, matrixRes2, row3, cols3, row3, cols3);
//
//	if (TestComparisonMatrix(matrixRes1, row3, cols3, matrixRes2, row3, cols3)) {
//		return true;
//	}
//	else {
//		std::cout << "The Test 4 will fail!" << std::endl;
//		return false;
//	}
//}


void TestAll() {
	Test1_2();
	//if (Test1() || Test2() || Test3() || Test4()) {
	//	std::cout << "Tests passed!" << std::endl;
	//}
}