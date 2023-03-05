#include "stdafx.h"

const std::string BASE_SYMBOLS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int BASE_OF_DECIMAL_SYSTEM = 10;

void CheckOverflow(const int& result, const int& radix, const int& degree, const int& digit, bool& wasError)
{
	if (radix > pow(INT_MAX, (1.0 / degree)))
	{
		wasError = true;
	}
	else if (digit > INT_MAX / pow(radix, degree))
	{
		wasError = true;
	}
	else if (result > INT_MAX - digit * pow(radix, degree))
	{
		wasError = true;
	}

	if (wasError)
	{
		std::cout << "Overflow" << std::endl;
	}
}

void CheckComplianceWithNumberSystem(const int& digit, const int& radix, bool& wasError)
{
	if (digit >= radix)
	{
		std::cout << "The number should not consist of digits that do not belong to "
			<< "its number system" << std::endl;
		wasError = true;
	}
}

void checkCorrectChar(const int& digit, bool& wasError)
{
	if (digit == BASE_SYMBOLS.npos)
	{
		std::cout << "Incorrect input char" << std::endl;
		wasError = true;
	}
}

int StringToInt(const std::string& str, const int& radix, bool& wasError)
{
	int result = 0;
	int degree = 0;

	for (int counter = str.length() - 1; counter >= 0; counter--)
	{
		int digit = (int)BASE_SYMBOLS.find(str[counter]);

		checkCorrectChar(digit, wasError);
		if (wasError)
		{
			return result;
		}

		CheckComplianceWithNumberSystem(digit, radix, wasError);
		if (wasError)
		{
			return result;
		}

		CheckOverflow(result, radix, degree, digit, wasError);
		if (wasError)
		{
			return result;
		}

		result += (int)(digit * pow(radix, degree));
		degree++;
	}

	return result;
}

std::string IntToString(int n, int radix)
{
	std::string result = "";
	int remained = n;

	while (remained >= radix)
	{
		result.insert(result.begin(), BASE_SYMBOLS[remained % radix]);
		remained = remained / radix;
	}
	result.insert(result.begin(), BASE_SYMBOLS[remained % radix]);

	return result;
}

std::string ConvertNumber(const std::string& sourceNotation, const std::string& destinationNotation,
	const std::string& value, bool& wasError)
{
	int source = StringToInt(sourceNotation, BASE_OF_DECIMAL_SYSTEM, wasError);
	int destination = StringToInt(destinationNotation, BASE_OF_DECIMAL_SYSTEM, wasError);

	if (source > 36 || destination > 36 || source < 2 || destination < 2)
	{
		std::cout << "The number system must belong to [2; 36]" << std::endl;
		wasError = true;
		return value;
	}

	bool isNegative = false;
	std::string valueForTrans = value;

	if (value[0] == '-')
	{
		isNegative = true;
		valueForTrans.erase(0, 1);
	}

	std::string result = IntToString(StringToInt(valueForTrans, source, wasError),
		destination);

	if (isNegative)
	{
		result.insert(result.begin(), '-');
	}

	return result;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid argument count" << std::endl
			<< "Usage: radix.exe <source notation> <destination notation> <value>" << std::endl;
		return 1;
	}

	bool wasError = false;
	std::string result = ConvertNumber(argv[1], argv[2], argv[3], wasError);

	if (!wasError)
	{
		std::cout << result << std::endl;
	}

	return 0;
}