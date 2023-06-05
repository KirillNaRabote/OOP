#include "stdafx.h"

const std::string BASE_SYMBOLS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int BASE_OF_DECIMAL_SYSTEM = 10;

void PrintMessage(const std::string mess)
{
	std::cout << mess << std::endl;
}

//Сложно и непонятно. С отрицательным числом не сработало
bool CheckOverflow(int result, int radix, int degree, int digit)
{
	bool wasError = false;
	//не использовать возведение в степень
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
		PrintMessage("Overflow");
	}

	return wasError;
}

bool CheckComplianceWithNumberSystem(int digit, int radix)
{
	if (digit >= radix)
	{
		PrintMessage("The number should not consist of digits that do not belong to its number system");
		return false;
	}

	return true;
}
//Не используется выходное значение, но используется входной параметр. Странное решение. Название функции не по стилю
//Функция не делает, что обещает, либо делает, но очень странно. Зачем на нужна?
//Зачем функция выводит что-то?
bool CheckCorrectChar(int digit)
{
	if (digit == BASE_SYMBOLS.npos)
	{
		PrintMessage("Incorrect input char");
		return false;
	}

	return true;
}
int StringToInt(const std::string& str, int radix, bool& wasError)
{
	wasError = false;
	int result = 0;
	for (int counter = str.length() - 1, degree = 0; counter >= 0; counter--, degree++)
	{
		int digit = static_cast<int>(BASE_SYMBOLS.find(str[counter]));

		if (wasError = !CheckCorrectChar(digit) || !CheckComplianceWithNumberSystem(digit, radix) || CheckOverflow(result, radix, degree, digit))
		{
			return result;
		}

		result += static_cast<int>(digit * pow(radix, degree));
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
	wasError = false;
	int source = StringToInt(sourceNotation, BASE_OF_DECIMAL_SYSTEM, wasError);
	int destination = StringToInt(destinationNotation, BASE_OF_DECIMAL_SYSTEM, wasError);

	if (source > 36 || destination > 36 || source < 2 || destination < 2)
	{
		PrintMessage("The number system must belong to [2; 36]");
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
//не работает с самым маленьким числом INT_MIN