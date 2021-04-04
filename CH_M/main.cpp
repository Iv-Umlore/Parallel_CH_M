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
const int block_size = 2;//100;
const int defaultMatrixSize = 5;

// Создание симметричной положительноопределённой матрицы 
// A11 A21T
// A21 A22
//
void GetMainSimetricMatrix(double* result, int size) {

	srand(time(0));
	// i - column, j - line
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < j; i++)
			result[j * size + i] = std::rand() % 75;

		result[j * size + j] = 76 + std::rand() % 25;
	}
}

void GetElement(double* aMatrix, double* element, int line, int column, int mSize) {
	if (line > column)
		*element = aMatrix[line * mSize + column];
	else
		*element = aMatrix[column * mSize + line];
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
				std::cout << std::setprecision(4) << matrix[i * size + j] << "\t";
		std::cout << std::endl;
	}
}

void Method(double* aMatrix, double* bMatrix, int startIndexColumn, int bSize, int mSize, int startIndexLine = -1) {

	if (startIndexLine == -1) {
		startIndexLine = startIndexColumn;



	}
	else 
		for (int i = startIndexColumn; i < startIndexColumn + bSize; i++) {

			GetElement(aMatrix, &bMatrix[i * mSize + i], i, i, mSize);
			bMatrix[i * mSize + i] = aMatrix[i * mSize + i];

			for (int k = startIndexColumn; k < i - 1; k++)
				bMatrix[i * mSize + i] -= bMatrix[i * mSize + k] * bMatrix[i * mSize + k];

			bMatrix[i * mSize + i] = sqrt(bMatrix[i * mSize + i]);

			for (int j = i + 1; j < startIndexColumn + bSize; j++) {
				GetElement(aMatrix, &bMatrix[j * mSize + i], j, i, mSize);

				for (int k = 0; k < i; k++)
					bMatrix[j * mSize + i] -= bMatrix[i * mSize + k] * bMatrix[j * mSize + k];

				bMatrix[j * mSize + i] /= bMatrix[i * mSize + i];
			}
		}

}

void GetLPart(double* aMatrix, double* resultLPart, int mSize) {
	for (int i = 0; i < mSize; i++)
		for (int j = 0; j < mSize; j++)
			if (i != j)
				resultLPart[i * mSize + j] = 0;
	int i = 0;

	while (i < mSize - block_size) {
		Method(aMatrix, resultLPart, i, block_size, mSize);
		i += block_size;
		int j = 0;

	}

	Method(aMatrix, resultLPart, i, mSize - i, mSize);
}

//double* MatrixMyltiply(double* fMatrix, double* sMatrix) {
//	double *  resultLPart = new double[1];
//	return resultLPart;
//}

void DefaultDecomposition(double* pMatrix, double* resultLPart, int size) {
	
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			resultLPart[j * size + i] = 0;

	for (int i = 0; i < size; i++) {
		GetElement(pMatrix, &resultLPart[i * size + i], i, i, size);
		for (int k = 0; k < i - 1; k++)

			resultLPart[i * size + i] -= resultLPart[i * size + k] * resultLPart[i * size + k];
		resultLPart[i * size + i] = sqrt(resultLPart[i * size + i]);
		
		for (int j = i + 1; j < size; j++) {
			GetElement(pMatrix, &resultLPart[j * size + i], j, i, size);
			for (int k = 0; k < i; k++)
				resultLPart[j * size + i] -= resultLPart[i * size + k] * resultLPart[j * size + k];
			resultLPart[j * size + i] /= resultLPart[i * size + i];
		}
	}

}

int main()
{

	auto aMatrix = new double[defaultMatrixSize * defaultMatrixSize];
	GetMainSimetricMatrix(aMatrix, defaultMatrixSize);

	double* LPart = new double[defaultMatrixSize * defaultMatrixSize];
	DefaultDecomposition(aMatrix, LPart, defaultMatrixSize);

	PrintMainMatrix(aMatrix, defaultMatrixSize);
	std::cout << std::endl;

	PrintMatrix(LPart, defaultMatrixSize);
	std::cout << std::endl;

	GetLPart(aMatrix, LPart, defaultMatrixSize);
	PrintMatrix(LPart, defaultMatrixSize);
	std::cout << std::endl;

	system("pause");
}
