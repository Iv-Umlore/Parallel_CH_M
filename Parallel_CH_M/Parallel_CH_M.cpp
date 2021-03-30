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

double * GetLPart(double* aMatrix, int mSize) {
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



    std::cout << "Hello World!\n"; 
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
