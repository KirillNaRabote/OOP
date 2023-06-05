#include "FillVector.h"

#include <iostream>

std::vector<double> FillVectorWithNumbers(std::istream& input)
{
	std::vector<double> vectorNumbers;
	double number;

	while (input >> number)
	{
		vectorNumbers.push_back(number);
	}

	return vectorNumbers;
}