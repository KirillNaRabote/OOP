#include "stdafx.h"

const int MATRIX_SIZE = 3;

using Matrix = std::vector<std::vector<double>>;

Matrix InitMatrix(std::ifstream& matrixFile, bool& wasError)
{
	wasError = false;
	Matrix matrix;
	std::vector<double> matrixLine;
	double coefficientValue = 0;
	int coefficientCount = 0;

	while (matrixFile >> coefficientValue)
	{
		matrixLine.push_back(coefficientValue);
		coefficientCount++;

		if (matrixLine.size() == MATRIX_SIZE)
		{
			matrix.push_back(matrixLine);
			matrixLine.clear();
		}
	}

	if (coefficientCount > MATRIX_SIZE * MATRIX_SIZE || coefficientCount < MATRIX_SIZE * MATRIX_SIZE)
	{
		wasError = true;
	}

	return matrix;
}

double FindMinor(Matrix matrix, const int& lineNumber, const int& columnNumber)
{
	Matrix minor;
	std::vector<double> minorLine;

	for (int lineCount = 0; lineCount < MATRIX_SIZE; lineCount++)
	{
		for (int columnCount = 0; columnCount < MATRIX_SIZE; columnCount++)
		{
			if (lineCount != lineNumber && columnCount != columnNumber)
			{
				minorLine.push_back(matrix[lineCount][columnCount]);
			}
			if (minorLine.size() == 2)
			{
				minor.push_back(minorLine);
				minorLine.clear();
			}
		}
	}

	return minor[0][0] * minor[1][1] - minor[0][1] * minor[1][0];
}

double FindDeterminant(Matrix matrix)
{
	return matrix[0][0] * FindMinor(matrix, 0, 0) -
		matrix[0][1] * FindMinor(matrix, 0, 1) + matrix[0][2] * FindMinor(matrix, 0, 2);
}

double FindAlgebraicComplement(Matrix matrix, const int& lineNumber, const int& columnNumber)
{
	return pow(-1, lineNumber + columnNumber + 2) * FindMinor(matrix, lineNumber, columnNumber);
}

std::vector<std::vector<double>> FindInverseMatrix(Matrix matrix, bool& zeroDeterminant)
{
	double determinant = FindDeterminant(matrix);

	if (determinant == 0)
	{
		zeroDeterminant = true;
		return matrix;
	}

	Matrix inverseMatrix;
	std::vector<double> inverseMatrixLine;

	for (int lineCount = 0; lineCount < MATRIX_SIZE; lineCount++)
	{
		for (int columnCount = 0; columnCount < MATRIX_SIZE; columnCount++)
		{
			inverseMatrixLine.push_back(
				FindAlgebraicComplement(matrix, columnCount, lineCount) / determinant
			);
		}
		inverseMatrix.push_back(inverseMatrixLine);
		inverseMatrixLine.clear();
	}

	return inverseMatrix;
}

void PrintMatrix(Matrix matrix, std::ostream& output)
{
	for (int lineCount = 0; lineCount < MATRIX_SIZE; lineCount++)
	{
		for (int columnCount = 0; columnCount < MATRIX_SIZE; columnCount++)
		{
			if (matrix[lineCount][columnCount] == 0)
			{
				output << 0 << " ";
			}
			else
			{
				output << std::fixed << std::setprecision(3) << matrix[lineCount][columnCount] << " ";
			}
		}
		output << std::endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count" << std::endl
			<< "Usage: invert.exe <matrix file>" << std::endl;
		return 1;
	}

	Matrix matrix;
	std::ifstream matrixFile(argv[1]);
	bool wasError = false;

	matrix = InitMatrix(matrixFile, wasError);
	if (wasError)
	{
		std::cout << "The matrix should be 3x3 in size" << std::endl;
		return 0;
	}

	bool zeroDeterminant = false;
	Matrix inverseMatrix = FindInverseMatrix(matrix, zeroDeterminant);

	if (zeroDeterminant)
	{
		std::cout << "There is no inverse matrix, since the determinant is zero" << std::endl;
	}
	else
	{
		PrintMatrix(inverseMatrix, std::cout);
	}

	return 0;
}