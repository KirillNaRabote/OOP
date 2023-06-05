#include "AddToEach.h"
#include "Print.h"
#include "FillVector.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	//неправильно вынес функции по модулям
	std::vector<double> vectorNumbers = FillVectorWithNumbers(std::cin);

	std::cout << "Sorted input vector:" << std::endl;
	PrintVector(std::cout, vectorNumbers);

	AddArithmeticMeanOfPositiveNumbers(vectorNumbers);

	sort(vectorNumbers.begin(), vectorNumbers.end());

	std::cout << "Vector after addition:" << std::endl;
	PrintVector(std::cout, vectorNumbers);

	return 0;
}