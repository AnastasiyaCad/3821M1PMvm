#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.h>

#include "CreateMatrix.h"
#include "OpenCL.h"

const char* mult_matrex_kernel = 
"__kernel void mult_matrex_square (										\n"\
"						__global int* matrixA,							\n"\
"						__global int* matrixB,							\n"\
"						__global int* matrixRes,						\n"\
"						int rowA, int colsA,							\n"\
"						int rowB, int colsB								\n"\
"						) {											    \n"\
"	int col = get_global_id(0);										    \n"\
"	int row = get_global_id(1);											\n"\
"	int sum = 0;														\n"\
"	for (int i = 0; i < colsA; i++) {									\n"\
"		sum += matrixA[row * colsA + i] * matrixB[i * colsB + col];		\n"\
"	}																    \n"\
"	matrixRes[row * colsB + col] = sum; 							    \n"\
"}";

double openclMatrix(int* matrixA, int* matrixB, int* matrixRes, int rowA, int colsA, int rowB, int colsB) {
	cl_int err;

	cl_uint numPlatforms = 0;
	clGetPlatformIDs(0, NULL, &numPlatforms);

	cl_platform_id platform = NULL;
	cl_platform_id* platforms = new cl_platform_id[numPlatforms];
	clGetPlatformIDs(numPlatforms, platforms, NULL);
	platform = platforms[0];

	cl_uint deviceCount = 0;

	cl_device_id device;
	cl_device_id* devices = new cl_device_id[deviceCount];

	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, devices, &deviceCount);
	std::cout << err << std::endl;
	device = devices[0];

	size_t source_size = strlen(mult_matrex_kernel);

	cl_context context = clCreateContext(NULL, 1, &devices[0], NULL, NULL, NULL);

	cl_command_queue command_queue;
	command_queue = clCreateCommandQueueWithProperties(context, devices[0], 0, NULL);

	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&mult_matrex_kernel, (const size_t*)&source_size, NULL);

	cl_mem input1 = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * colsA * rowA, NULL, NULL);
	cl_mem input2 = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * colsB * rowB, NULL, NULL);
	cl_mem output = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * colsB * rowA, NULL, NULL);

	err = clEnqueueWriteBuffer(command_queue, input1, CL_TRUE, 0, sizeof(int) * colsA * rowA, matrixA, 0, NULL, NULL);
	std::cout << err << std::endl;
	err = clEnqueueWriteBuffer(command_queue, input2, CL_TRUE, 0, sizeof(int) * colsB * rowB, matrixB, 0, NULL, NULL);
	std::cout << err << std::endl;
	err = clEnqueueWriteBuffer(command_queue, output, CL_TRUE, 0, sizeof(int) * colsB * rowA, matrixRes, 0, NULL, NULL);
	std::cout << err << std::endl;

	err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
	std::cout << err << std::endl;
	if (err != 0) {
		size_t len = 0;
		cl_int ret = CL_SUCCESS;
		ret = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
		char* buffer = (char*)calloc(len, sizeof(char));
		ret = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, len, buffer, NULL);
		std::cout << buffer << std::endl;
	}
	cl_kernel kernel = clCreateKernel(program, "mult_matrex_square", NULL);

	clSetKernelArg(kernel, 0, sizeof(cl_mem), &input1);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &input2);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), &output);
	clSetKernelArg(kernel, 3, sizeof(int), &rowA);
	clSetKernelArg(kernel, 4, sizeof(int), &colsA);
	clSetKernelArg(kernel, 5, sizeof(int), &rowB);
	clSetKernelArg(kernel, 4, sizeof(int), &colsB);

	size_t global_work_size[2] = { rowA, colsA };
	size_t size[2] = { 16, 16 };
	cl_event event;

	size_t maxWorkGroupSize;
	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE,
		sizeof(size_t), &maxWorkGroupSize, NULL);
	std::cout << maxWorkGroupSize << std::endl;

	double start = omp_get_wtime();
	if ((global_work_size[0] % size[0] != 0)|| (global_work_size[1] % size[1] != 0)) {
		//size_t size_loc[2] = { NULL, NULL };
		err = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global_work_size, NULL, 0, NULL, &event);
	}
	else {
		err = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global_work_size, size, 0, NULL, &event);
	}
	//clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global_work_size, size, 0, NULL, &event);
	//std::cout << event << std::endl;
	std::cout << clWaitForEvents(1, &event) << std::endl;
	std::cout << err << std::endl;


	clEnqueueReadBuffer(command_queue, output, CL_TRUE, 0, sizeof(int) * rowA * colsB, matrixRes, 0, NULL, NULL);
	double end = omp_get_wtime();

	clReleaseMemObject(input1);
	clReleaseMemObject(input2);
	clReleaseMemObject(output);
	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);

	return end - start;

}


double opencl_multiply_matrix(int* matrixA, int* matrixB, int* matrixRes, int rowA, int colsA, int rowB, int colsB) {
	cl_int err;
	cl_uint numPlatforms = 0;
	clGetPlatformIDs(0, NULL, &numPlatforms);
	clGetPlatformIDs(0, NULL, &numPlatforms);

	cl_platform_id platform = NULL;

	cl_platform_id* platforms = new cl_platform_id[numPlatforms];
	clGetPlatformIDs(numPlatforms, platforms, NULL);

	platform = platforms[0];

	delete[] platforms;

	// создание контекста

	cl_context_properties properties[3] = {
		CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0
	};

	cl_context context = clCreateContextFromType(
		(NULL == platform) ? NULL : properties, CL_DEVICE_TYPE_GPU, NULL, NULL, NULL);

	// определние размера массива для хвранения списка устройств
	size_t size = 0;
	clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &size);

	// выбор девайса
	cl_device_id device;
	cl_device_id* devices = (cl_device_id*)alloca(size);
	clGetContextInfo(context, CL_CONTEXT_DEVICES, size, devices, NULL);

	device = devices[0];

	//delete[] devices;

	// создание очереди команд для заданного контекста и выбранного устройства 

	cl_command_queue command_queue = clCreateCommandQueue(context, device, 0, NULL); 
	//clCreateCommandQueueWithProperties
	
	// создание программного объекта для из исходного объекта

	size_t srclen[] = { strlen(mult_matrex_kernel) };

	cl_program program = clCreateProgramWithSource(context, 1, &mult_matrex_kernel, srclen, NULL);

	// создание исполняемого файла программы для выбранного устройства

	clBuildProgram(program, 1, &device, NULL, NULL, NULL);

	// создание объекта ядра

	cl_kernel kernel = clCreateKernel(program, "mult_matrex_square", NULL);

	// создание входного и выходного буфера

	cl_mem input1 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int) * rowA * colsA, NULL, NULL);
	cl_mem input2 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int) * rowB * colsB, NULL, NULL);
	cl_mem output = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * rowA * colsB, NULL, NULL);

	// копирование входного буфера в память устройтсва

	clEnqueueWriteBuffer(command_queue, input1, CL_TRUE, 0, sizeof(int) * rowA * colsA, matrixA, 0, NULL, NULL);
	clEnqueueWriteBuffer(command_queue, input2, CL_TRUE, 0, sizeof(int) * rowB * colsB, matrixB, 0, NULL, NULL);
	clEnqueueWriteBuffer(command_queue, output, CL_TRUE, 0, sizeof(int) * rowA * colsB, matrixRes, 0, NULL, NULL);

	// утсновка агрументов ядра

	clSetKernelArg(kernel, 0, sizeof(cl_mem), &input1);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &input2);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), &output);
	clSetKernelArg(kernel, 3, sizeof(int), &rowA);
	clSetKernelArg(kernel, 4, sizeof(int), &colsA);
	clSetKernelArg(kernel, 5, sizeof(int), &rowB);
	clSetKernelArg(kernel, 4, sizeof(int), &colsB);
	
	// опредление глобального и локального размеров работы и запуск ядра

	size_t global_work_size[2] = { rowA, colsA };
	size_t size_loc[2] = { 16, 16 };

	cl_event event;


	double start = omp_get_wtime();
	if ((global_work_size[0] % size_loc[0] != 0) || (global_work_size[1] % size_loc[1] != 0)) {
		size_t size_loc2[2] = { NULL, NULL };
		err = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global_work_size, size_loc2, 0, NULL, &event);
	}
	else {
		err = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global_work_size, size_loc, 0, NULL, &event);
	}

	std::cout << err << std::endl;

	//clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global_work_size, size_loc, 0, NULL, &event);
	//clWaitForEvents(1, &event);

	// ожидание завершения всех команд в очереди

	clFinish(command_queue);

	double end = omp_get_wtime();

	clEnqueueReadBuffer(command_queue, output, CL_TRUE, 0, sizeof(int) * rowA * colsB, matrixRes, 0, NULL, NULL);

	clReleaseMemObject(input1);
	clReleaseMemObject(input2);
	clReleaseMemObject(output);
	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);

	return end - start;
}


const char* mult_matrex_optim_kernel =
"__kernel void mult_matrex_optim_square (										\n"\
"						__global int* matrixA,							\n"\
"						__global int* matrixB,							\n"\
"						__global int* matrixRes,						\n"\
"						int rowA, int colsA,							\n"\
"						int rowB, int colsB								\n"\
"						) {											    \n"\
"	int BLOCK_SIZE = 16;										    \n"\
"	__local int A_local[BLOCK_SIZE][BLOCK_SIZE]; \n"\
"	__local int B_local[BLOCK_SIZE][BLOCK_SIZE]; \n"\
"	int col = get_global_id(0);										    \n"\
"	int row = get_global_id(1);											\n"\
"	int col_local = get_local_id(0);										    \n"\
"	int row_local = get_local_id(1);											\n"\
"	int A_start = rowA * BLOCK_SIZE * row; 	\n"\
"	int A_end = A_start + rowA - 1;	\n"\
"	int B_start = BLOCK_SIZE * col;  \n"\
"	int sum = 0; \n"\
"	for (int a = A_start, b = B_start; a <= A_end; a += BLOCK_SIZE, b += (BLOCK_SIZE * rowB)) {\n"\
"		A_local[col_local][row_local] = A[a + rowA * row_local + col_local]; \n"\
"		B_local[col_local][row_local] = B[b + rowB * row_local + local_x]; \n"\
"		barrier(CLK_LOCAL_MEM_FENCE);\n"\
"		for (int k = 0; k < BLOCK_SIZE; ++k) { \n"\
"			sum += A_local[k][row_local] * B_local[col_local][k]; \n"\
"		}																						\n"\
"		barrier(CLK_LOCAL_MEM_FENCE); \n"\
"	} \n"\
"	matrixRes[row * get_global_size(0) + col] = sum; \n"\
"}";

double opencl_multiply_matrix_optim(int* matrixA, int* matrixB, int* matrixRes, int rowA, int colsA, int rowB, int colsB) {
	cl_uint numPlatforms = 0;
	clGetPlatformIDs(0, NULL, &numPlatforms);
	clGetPlatformIDs(0, NULL, &numPlatforms);

	cl_platform_id platform = NULL;

	cl_platform_id* platforms = new cl_platform_id[numPlatforms];
	clGetPlatformIDs(numPlatforms, platforms, NULL);

	platform = platforms[0];

	delete[] platforms;

	// создание контекста

	cl_context_properties properties[3] = {
		CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0
	};

	cl_context context = clCreateContextFromType(
		(NULL == platform) ? NULL : properties, CL_DEVICE_TYPE_GPU, NULL, NULL, NULL);

	// определние размера массива для хвранения списка устройств
	size_t size = 0;
	clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &size);

	// выбор девайса
	cl_device_id device;
	cl_device_id* devices = (cl_device_id*)alloca(size);
	clGetContextInfo(context, CL_CONTEXT_DEVICES, size, devices, NULL);

	device = devices[0];

	//delete[] devices;

	// создание очереди команд для заданного контекста и выбранного устройства 

	cl_command_queue command_queue = clCreateCommandQueue(context, device, 0, NULL);
	//clCreateCommandQueueWithProperties

	// создание программного объекта для из исходного объекта

	size_t srclen[] = { strlen(mult_matrex_optim_kernel) };

	cl_program program = clCreateProgramWithSource(context, 1, &mult_matrex_optim_kernel, srclen, NULL);

	// создание исполняемого файла программы для выбранного устройства

	clBuildProgram(program, 1, &device, NULL, NULL, NULL);

	// создание объекта ядра

	cl_kernel kernel = clCreateKernel(program, "mult_matrex_optim_square", NULL);

	// создание входного и выходного буфера

	cl_mem input1 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(size_t) * rowA * colsA, NULL, NULL);
	cl_mem input2 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(size_t) * rowB * colsB, NULL, NULL);
	cl_mem output = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(size_t) * rowA * colsB, NULL, NULL);

	// копирование входного буфера в память устройтсва

	clEnqueueWriteBuffer(command_queue, input1, CL_TRUE, 0, sizeof(size_t) * rowA * colsA, matrixA, 0, NULL, NULL);
	clEnqueueWriteBuffer(command_queue, input2, CL_TRUE, 0, sizeof(size_t) * rowB * colsB, matrixB, 0, NULL, NULL);
	clEnqueueWriteBuffer(command_queue, output, CL_TRUE, 0, sizeof(size_t) * rowA * colsB, matrixRes, 0, NULL, NULL);

	// утсновка агрументов ядра

	clSetKernelArg(kernel, 0, sizeof(cl_mem), &input1);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &input2);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), &output);
	clSetKernelArg(kernel, 3, sizeof(int), &rowA);
	clSetKernelArg(kernel, 4, sizeof(int), &colsA);
	clSetKernelArg(kernel, 5, sizeof(int), &rowB);
	clSetKernelArg(kernel, 4, sizeof(int), &colsB);

	// опредление глобального и локального размеров работы и запуск ядра

	size_t global_work_size[2] = { rowA, colsA };
	size_t size_loc[2] = { 16, 16 };

	cl_event event;

	double start = omp_get_wtime();

	clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global_work_size, size_loc, 0, NULL, &event);
	//clWaitForEvents(1, &event);

	// ожидание завершения всех команд в очереди

	clFinish(command_queue);

	double end = omp_get_wtime();

	clEnqueueReadBuffer(command_queue, output, CL_TRUE, 0, sizeof(int) * rowA * colsB, matrixRes, 0, NULL, NULL);

	clReleaseMemObject(input1);
	clReleaseMemObject(input2);
	clReleaseMemObject(output);
	clReleaseProgram(program);
	clReleaseKernel(kernel);
	clReleaseCommandQueue(command_queue);
	clReleaseContext(context);

	return end - start;
}