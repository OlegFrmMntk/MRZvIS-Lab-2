// Лабораторная работа 2 по дисциплине МРЗвИС
// Выполнена студентом группы 821703
// БГУИР, Манкевич Олег Александрович
// Описание класса конвеера
// 18.05.2020


#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <thread>
#include <mutex>

using namespace std;

class Conveyer
{
	// Размеры матриц A, B, E, G (pxm, mxq, 1xm, pxq) 
	int p, m, q;

	// Ранг
	int rank;
	
	// Время выполнения операций
	int multiplicationTime = 1;
	int additionTime = 1;
	int subtractionTime = 1;
	int comparisonTime = 1;

	// Количество вызовов операций
	int numberOfMultiplications;
	int numberOfAdditions;
	int numberOfSubtractions;
	int numberOfComparisons;

	// Время работы конвеера
	int consistentTime;
	int parallelTime;
	int averageTime;

	// Ускорение
	int accelerationFactor;

	// Эффективность
	int efficiency;

	// Среднее время работы
	int averageLength;

	// Различие
	int discrepancy;

	// Количество процессорных элементов
	int nValue = 2;
	
	// Вычислить произведение всех чисел вектора.
	double procSetMultiplication(vector <double> numbers);

	// Вычислить произведение всех чисел вектора в формате (1 - x1) * (1 - x2)...(1 - xn).
	double procSetMultiplicationOneMinusNumber(vector <double> numbers);

	// Найти супремиум.
	double sup(const double& firstNumber, const double& secondNumber);

	// Найти минимум из двух чисел
	double minForTwo(const double& firstNumber, const double& secondNumber);
	
	// Найти максимум из двух чисел
	double maxForTwo(const double& firstNumber, const double& secondNumber);

	// Формирует случайное число x в промежутке [fMin;fMax]
	double fRand(double fMin, double fMax);

	// Генерирует матрицу со случайными значениями
	vector<vector<double>> generateMatrix(int firstSize, int secondSize);

public:

	// Матрицы
	vector <double> e;
	vector <vector <double>> a, b, c, g;
	vector <vector <vector <double>>> d, f;

	Conveyer();
	Conveyer(const int& p, const int& m, const int& q, const int& n);

	void start();

	void generate();

	void setP(int p);
	void setM(int m);
	void setQ(int q);

	void setA(vector <vector <double>> a);
	void setB(vector <vector <double>> b);
	void setE(vector <double> e);
	void setG(vector <vector <double>> g);

	vector <vector <double>> getC();
	vector <vector <vector <double>>> getD();
	vector <vector <vector <double>>> getF();

	void printNumbersList(vector <double> numbers);
	void printMatrix(vector<vector <double>> matrix);

	void procMatrixC();
	void procMatrixD();
	void procMatrixF();
};

