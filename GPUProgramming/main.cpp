#include "OpenMP.h"
#include "OpenCL.h"
#include "Tests.h"


int SIZE = 1024;
int BLOCK_SIZE = 16;

int main() { 
	Test1_2();

	//TestAll();

	//int row1 = SIZE;
	//int cols1 = SIZE;
	//int* matrix1 = new int[row1 * cols1];
	//CreateMatrix(matrix1, row1, cols1);

	//int row2 = SIZE;
	//int cols2 = SIZE;
	//int* matrix2 = new int[row2 * cols2];
	//CreateMatrix(matrix2, row2, cols2);

	//int row3 = SIZE;
	//int cols3 = SIZE;
	//int* matrix31 = new int[row3 * cols3];

	//int* matrix32 = new int[row3 * cols3];

	//int* matrix33 = new int[row3 * cols3];

	//int* matrix34 = new int[row3 * cols3];

	//double timeCPU = openmp_multiply_matrix_serial(matrix1, matrix2, matrix31, row1, cols1, row2, cols2);
	//double timeOMP = openmp_multiply_matrix_parallel(matrix1, matrix2, matrix32, row1, cols1, row2, cols2);
	//double timeGPU = opencl_multiply_matrix(matrix1, matrix2, matrix33, row1, cols1, row2, cols2);
	//double timeGPUopt = opencl_multiply_matrix_optim(matrix1, matrix2, matrix34, row1, cols1, row2, cols2);
	//

	//std::cout << "CPU = " << timeCPU << std::endl;
	//std::cout << "OMP = " << timeOMP << std::endl;
	//std::cout << "OCL = " << timeGPU << std::endl;
	//std::cout << "OCL_opt = " << timeGPUopt << std::endl;

	////std::cout << "CPU/OMP = " << timeCPU / timeOMP << std::endl;
	////std::cout << "OCL/OCL_opt = " << timeGPU / timeGPUopt << std::endl;

	////std::cout << 1.67e-05 / 4 << " " << 4.29992e-06;

	return 0;
}