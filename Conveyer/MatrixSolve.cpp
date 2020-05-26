// Лабораторная работа 2 по дисциплине МРЗвИС
// Выполнена студентом группы 821703
// БГУИР, Манкевич Олег Александрович
// Файл для тестирование конвеера
// 18.05.2020

#include <iostream>
#include "Conveyer.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	int p, m, q, n;

	cout << "Введите p: ";
	cin >> p;

	cout << "Введите m: ";
	cin >> m;

	cout << "Введите q: ";
	cin >> q;

	cout << "Введите n: ";
	cin >> n;

	cout << endl;

	Conveyer conveyer(p, m, q, n);
	
	conveyer.start();

	cout << "Матрица A:\n";
	conveyer.printMatrix(conveyer.a);
	cout << endl;

	cout << "Матрица B:\n";
	conveyer.printMatrix(conveyer.b);
	cout << endl;
	
	cout << "Матрица E:\n";
	conveyer.printNumbersList(conveyer.e);
	cout << endl << endl;
	
	cout << "Матрица G:\n";
	conveyer.printMatrix(conveyer.g);
	
	cout << "\n---------------------------------\n\n";

	cout << "Матрица С:\n";
	conveyer.printMatrix(conveyer.getC());
	cout << endl;

	cout << "Матрица D:\n";
	for (auto matrix : conveyer.getD()) {
		conveyer.printMatrix(matrix);
		cout << "--\n";
	}
	cout << endl;

	cout << "Матрица F:\n";
	for (auto matrix : conveyer.getF()) {
		conveyer.printMatrix(matrix);
		cout << "--\n";
	}
	cout << endl;

	return 0;
}