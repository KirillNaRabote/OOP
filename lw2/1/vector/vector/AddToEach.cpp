#include "AddToEach.h";
#include <numeric>
#include <algorithm>

double FindArithmeticMeanOfPositiveNumbers(const std::vector<double>& vectorNumbers)
{
	size_t positiveNumbersCount = 0;

	auto AddIfPositive = [&positiveNumbersCount](double acc, double current)
	{
		if (current > 0)
		{
			positiveNumbersCount++;
			return acc + current;
		}

		return acc;
	};

	auto sumOfPositives = std::accumulate(vectorNumbers.begin(), vectorNumbers.end(), 0.0, AddIfPositive);

	double avg = (positiveNumbersCount > 0) ? sumOfPositives / positiveNumbersCount : 0;

	return avg;
}

void AddArithmeticMeanOfPositiveNumbers(std::vector<double>& vectorNumbers)
{
	double arithmeticMeanOfPositiveNumbers = FindArithmeticMeanOfPositiveNumbers(vectorNumbers);

	auto addArithmeticMean = [&arithmeticMeanOfPositiveNumbers](double number)
	{
		return number + arithmeticMeanOfPositiveNumbers;
	};
	std::transform(vectorNumbers.begin(), vectorNumbers.end(), vectorNumbers.begin(), addArithmeticMean);
}