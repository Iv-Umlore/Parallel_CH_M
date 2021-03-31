// Parallel_CH_M.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>

// Примерный размер блока
// L2: Всего 256 Мб. Всего 3 блока
// ~ 80 Мб -> ~ 10млн double -> ~ 3000 * 3000
// Свободная кэш память - 16 Мб.

// По условию задачи матрица должна быть не больше 1000, поэтому для текущей задачи возьму число 100 за сторону блока
const int block_size = 100;

// Создание симметричной положительноопределённой матрицы 
// A11 A21T
// A21 A22
//
double* GetMainSimetricMatrix(int size) {
	double* result = new double[size*size];

	// i - column, j - line
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < j; i++)	
			result[j * size + i] = std::rand() % 75;

			result[j * size + j] = 76 + std::rand() % 25;
	}

	return result;
}

void PrintMainMatrix(double* matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			if (i >= j)
				std::cout << matrix[i * size + j] << ' ';
			else
				std::cout << matrix[j * size + i] << ' ';
		std::cout << std::endl;
	}
}

double* GetLPart(double* aMatrix, int mSize) {
	double *  resultLPart = new double[mSize * mSize];

	for (int i = 0; i < mSize; i++)
		for (int j = 0; j < mSize; j++)
			if (i != j)
				resultLPart[i * mSize + j] = 0;

	return resultLPart;
}

double* MatrixMyltiply(double* fMatrix, double* sMatrix) {
	double *  resultLPart = new double[1];
	return resultLPart;
}

double* DefaultDecomposition(double* pMatrix){
	double *  resultLPart = new double[1];
	return resultLPart;
}

int main()
{

	int defaultSize = 20;

	auto aMatrix = GetMainSimetricMatrix(defaultSize);

	PrintMainMatrix(aMatrix, defaultSize);




    std::cout << "Hello World!\n"; 
}
