// Лабораторная работа 2 по дисциплине МРЗвИС
// Выполнена студентом группы 821703
// БГУИР, Манкевич Олег Александрович
// Файл с реализацией функций конвеера
// 18.05.2020

#include "Conveyer.h"

Conveyer::Conveyer()
{
	this->p = 0;
	this->m = 0;
	this->q = 0;
	this->numberOfMultiplications = 0;
	this->numberOfAdditions = 0;
	this->numberOfSubtractions = 0;
	this->numberOfComparisons = 0;
	this->consistentTime = 0;
	this->parallelTime = 0;
	this->averageTime = 0;
	this->accelerationFactor = 0;
	this->averageLength = 0;
	this->discrepancy = 0;
	this->efficiency = 0;
	this->rank = 0;
}

Conveyer::Conveyer(const int& p, const int& m, const int& q, const int& n)
{
	this->p = p;
	this->m = m;
	this->q = q;
	this->nValue = n;
	this->numberOfMultiplications = 0;
	this->numberOfAdditions = 0;
	this->numberOfSubtractions = 0;
	this->numberOfComparisons = 0;
	this->consistentTime = 0;
	this->parallelTime = 0;
	this->averageTime = 0;
	this->accelerationFactor = 0;
	this->averageLength = 0;
	this->discrepancy = 0;
	this->efficiency = 0;
	this->rank = 0;
}

double Conveyer::fRand(double fMin, double fMax)
{
	double number = (double)rand() / RAND_MAX;
	
	return fMin + number * (fMax - fMin);
}

double Conveyer::minForTwo(const double& firstNumber, const double& secondNumber)
{
	numberOfComparisons += 2;
	return min(firstNumber, secondNumber);
}

double Conveyer::maxForTwo(const double& firstNumber, const double& secondNumber)
{
	numberOfComparisons += 2;
	return max(firstNumber, secondNumber);
}

double Conveyer::procSetMultiplication(vector <double> numbers)
{
	double answer = double(1);
	for (double number : numbers) {
		answer *= number;
		numberOfMultiplications++;
	}
	numberOfMultiplications--;

	return answer;
}

double Conveyer::procSetMultiplicationOneMinusNumber(vector <double> numbers)
{
	double answer = double(1);
	for (double number : numbers) {
		answer *= (double(1) - number);
		numberOfMultiplications++;
		numberOfSubtractions++;
	}
	numberOfMultiplications--;

	return answer;
}

double Conveyer::sup(const double& firstNumber, const double& secondNumber)
{
	int delta = 1;
	while (min((1 - firstNumber + double(delta)), double(0)) > secondNumber) {
		delta -= 1;
		numberOfComparisons += 2;
		numberOfSubtractions += 2;
	}

	return delta;
}

void Conveyer::procMatrixD()
{
	d.clear();

	vector <vector <double>> tempI;
	for (int j = 0; j < q; j++) {
		vector <double> tempJ(m);
		tempI.push_back(tempJ);
	}

	for (int i = 0; i < p; i++) {
		d.push_back(tempI);
	}

	for (int i = 0; i < p; i++) {
		for (int j = 0; j < q; j++) {
			for (int k = 0; k < m; k++) {
				d[i][j][k] = maxForTwo(a[i][k] + b[k][j] - double(1), double(0));
				numberOfAdditions++;
				numberOfSubtractions--;
			}
		}
	}
	
	parallelTime += ceil((p * q * m) / nValue) * 2 * comparisonTime;
	averageTime += p * q * m * 2 * comparisonTime;
}

void Conveyer::procMatrixF()
{
	f.clear();

	vector <vector <double>> tempI;
	for (int j = 0; j < q; j++) {
		vector <double> tempJ(m);
		tempI.push_back(tempJ);
	}

	for (int i = 0; i < p; i++) {
		f.push_back(tempI);
	}

	for (int i = 0; i < p; i++) {
		for (int j = 0; j < q; j++) {
			for (int k = 0; k < m; k++) {
				
				double supForA = sup(a[i][k], b[k][j]);
				double supForB = sup(b[k][j], a[i][j]);
				
				f[i][j][k] = supForA * (double(2) * e[k] - double(1)) * e[k] + supForB * 
					        (double(1) + (double(4) * supForA - double(2)) * e[k]) * (double(1) - e[k]);

				numberOfMultiplications += 7;
				numberOfAdditions++;
				numberOfSubtractions += 3;
			}
		}
	}
	
	int timeValue = 7 * multiplicationTime + 2 * additionTime + 3 * subtractionTime + 3 * (2 * comparisonTime + subtractionTime);
	
	parallelTime += int(ceil((p * q * m) / nValue)) * timeValue;
	averageTime += p * q * m * timeValue;
}

void Conveyer::procMatrixC()
{
	c.clear();

	for (int j = 0; j < q; j++) {
		vector <double> tempJ(m);
		c.push_back(tempJ);
	}

	for (int i = 0; i < p; i++) {
		for (int j = 0; j < q; j++) {
				
				double multNumber = procSetMultiplication(f[i][j]);
				double multOneMinusNumber = procSetMultiplicationOneMinusNumber(d[i][j]);

				c[i][j] = multNumber * (double(3) * g[i][j] - double(2)) * g[i][j] + (double(1) - multOneMinusNumber +
						  (double(4) * minForTwo(multNumber, multOneMinusNumber) - double(3) * (double(1) - multOneMinusNumber)) * g[i][j]) *
					      (double(1) - g[i][j]);

				numberOfMultiplications += 7;
				numberOfAdditions += 2;
				numberOfSubtractions += 5;
		}
	}

	int timeValue = (6 * multiplicationTime + 2 * additionTime + 2 * subtractionTime + 3 * ((m - 1) * multiplicationTime + (m + 1) * subtractionTime) + 2 * 
		             ((m - 1) * multiplicationTime) + subtractionTime + additionTime + 2 * comparisonTime);
	
	parallelTime += int(ceil((p * q) / nValue)) * timeValue;
	averageTime += p * q * timeValue;
}

vector <vector <double>> Conveyer::generateMatrix(int firstSize, int secondSize)
{
	vector<vector<double>> matrix;
	vector<double> tempArray;

	for (int i = 0; i < firstSize; i++) {
		tempArray.clear();
		for (int j = 0; j < secondSize; j++) {
			tempArray.push_back(fRand((double)-1, (double)1));
		}
		matrix.push_back(tempArray);
	}

	return matrix;
}

void Conveyer::generate()
{
	a = generateMatrix(p, m);
	b = generateMatrix(m, q);

	e.clear();
	for (int j = 0; j < m; j++) {
		e.push_back(fRand((double)-1, (double)1));
	}

	g = generateMatrix(p, q);
}

void Conveyer::start()
{
	numberOfMultiplications = 0;
	numberOfAdditions = 0;
	numberOfSubtractions = 0;
	numberOfComparisons = 0;
	parallelTime = 0;
	consistentTime = 0;
	averageTime = 0;

	generate();

	procMatrixD();
	procMatrixF();
	procMatrixC();

	rank = m * p * q;

	consistentTime = numberOfMultiplications * multiplicationTime + numberOfAdditions * additionTime + numberOfSubtractions * subtractionTime + numberOfComparisons * comparisonTime;
	
	accelerationFactor = consistentTime / parallelTime;
	efficiency = consistentTime / (parallelTime * nValue);
	
	averageLength = ceil(averageTime / rank);
	discrepancy = (parallelTime / averageLength);
}

void Conveyer::setP(int p) {
	this->p = p;
}

void Conveyer::setM(int m) {
	this->m = m;
}

void Conveyer::setQ(int q) {
	this->q = q;
}

void Conveyer::setA(vector <vector <double>> a) {
	this->a = a;
}

void Conveyer::setB(vector <vector <double>> b) {
	this->b = b;
}

void Conveyer::setE(vector <double> e) {
	this->e = e;
}

void Conveyer::setG(vector <vector <double>> g) {
	this->g = g;
}

vector <vector <double>> Conveyer::getC() {
	return this->c;
}

vector <vector <vector <double>>> Conveyer::getD() {
	return this->d;
}

vector <vector <vector <double>>> Conveyer::getF() {
	return this->f;
}

void Conveyer::printNumbersList(vector <double> numbers)
{
	for (double number : numbers) {
		cout << number << " ";
	}
}

void Conveyer::printMatrix(vector <vector <double>> matrix)
{
	for (vector <double> numberList : matrix) {
		printNumbersList(numberList);
		cout << endl;
	}
}