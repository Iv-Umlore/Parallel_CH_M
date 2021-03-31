// Parallel_CH_M.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <omp.h>

// Для setprecision 
#include <iomanip>

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
void GetMainSimetricMatrix(double* result, int size) {

	// i - column, j - line
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < j; i++)
			result[j * size + i] = std::rand() % 75;

		result[j * size + j] = 76 + std::rand() % 25;
	}
}

void PrintMainMatrix(double* matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
			if (i >= j)
				std::cout << matrix[i * size + j] << '\t';
			else
				std::cout << matrix[j * size + i] << '\t';
		std::cout << std::endl;
	}
}

void PrintMatrix(double* matrix, int size) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
				std::cout << std::setprecision(5) << matrix[i * size + j] << "\t";
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

void DefaultDecomposition(double* pMatrix, double* resultLPart, int size) {
	
	for (int i = 0; i < size; i++) {		
		for (int k = 0; k < i - 1; k++)

			resultLPart[i * size + i] -= resultLPart[i * size + k] * resultLPart[i * size + k];
		resultLPart[i * size + i] = sqrt(pMatrix[i * size + i]);

		for (int j = i + 1; j < size; j++) {
			resultLPart[i * size + j] = 0;
			resultLPart[j * size + i] = pMatrix[j * size + i];
			for (int k = 0; k < i; k++)
				resultLPart[j * size + i] -= resultLPart[i * size + k] * resultLPart[j * size + k];
			resultLPart[j * size + i] /= resultLPart[i * size + i];
		}
	}

}

int main()
{

	int defaultSize = 5;

	auto aMatrix = new double[defaultSize * defaultSize];
	GetMainSimetricMatrix(aMatrix, defaultSize);

	double* LPart = new double[defaultSize * defaultSize];
	DefaultDecomposition(aMatrix, LPart, defaultSize);

	PrintMainMatrix(aMatrix, defaultSize);
	std::cout << std::endl;
	PrintMatrix(LPart, defaultSize);
	
	system("pause");
}
