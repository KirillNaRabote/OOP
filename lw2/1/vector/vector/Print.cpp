#include "Print.h"

#include <iostream>

void PrintVector(std::ostream& output, const std::vector<double>& vector)
{
	if (vector.empty())
	{
		output << "";
	}
	else
	{
		copy(vector.begin(), vector.end(), std::ostream_iterator<double>(output, " "));
		output << std::endl;
	}
}