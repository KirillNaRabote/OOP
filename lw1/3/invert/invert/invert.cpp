#include "stdafx.h"

const int MATRIX_COLUMNS = 3;
const int MATRIX_LINES = 3;

std::vector<std::vector<float>> InitMatrix(std::ifstream& matrixFile)
{
	std::vector<std::vector<float>> matrix;
	std::vector<float> matrixLine;
	float coefficientValue;

	while (matrixFile >> coefficientValue)
	{
		matrixLine.push_back(coefficientValue);

		if (matrixLine.size() == MATRIX_COLUMNS)
		{
			matrix.push_back(matrixLine);
			matrixLine.clear();
		}
	}

	return matrix;
}

float FindMinor(std::vector<std::vector<float>> matrix, const int& lineNumber, const int& columnNumber)
{
	std::vector<std::vector<float>> minorVector;
	std::vector<float> minorVectorLine;

	for (int lineCount = 0; lineCount < MATRIX_LINES; lineCount++)
	{
		for (int columnCount = 0; columnCount < MATRIX_COLUMNS; columnCount++)
		{
			if (lineCount != lineNumber && columnCount != columnNumber)
			{
				minorVectorLine.push_back(matrix[lineCount][columnCount]);
			}
			if (minorVectorLine.size() == 2)
			{
				minorVector.push_back(minorVectorLine);
				minorVectorLine.clear();
			}
		}
	}

	return minorVector[0][0] * minorVector[1][1] - minorVector[0][1] * minorVector[1][0];
}

float FindDeterminant(std::vector<std::vector<float>> matrix)
{
	return matrix[0][0] * FindMinor(matrix, 0, 0) -
		matrix[0][1] * FindMinor(matrix, 0, 1) + matrix[0][2] * FindMinor(matrix, 0, 2);
}

float FindAlgebraicComplement(std::vector<std::vector<float>> matrix, const int& lineNumber, const int& columnNumber)
{
	return pow(-1, lineNumber + columnNumber + 2) * FindMinor(matrix, lineNumber, columnNumber);
}

std::vector<std::vector<float>> FindInverseMatrix(std::vector<std::vector<float>> matrix, bool& zeroDeterminant)
{
	float determinant = FindDeterminant(matrix);

	if (determinant == 0)
	{
		zeroDeterminant = true;
		return matrix;
	}

	std::vector<std::vector<float>> inverseMatrix;
	std::vector<float> inverseMatrixLine;

	for (int lineCount = 0; lineCount < MATRIX_LINES; lineCount++)
	{
		for (int columnCount = 0; columnCount < MATRIX_COLUMNS; columnCount++)
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

void PrintMatrix(std::vector<std::vector<float>> matrix)
{
	for (int lineCount = 0; lineCount < MATRIX_LINES; lineCount++)
	{
		for (int columnCount = 0; columnCount < MATRIX_COLUMNS; columnCount++)
		{
			if (matrix[lineCount][columnCount] == 0)
			{
				std::cout << 0 << " ";
			}
			else
			{
				std::cout << std::fixed << std::setprecision(3) << matrix[lineCount][columnCount] << " ";
			}
		}
		std::cout << std::endl;
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

	std::vector<std::vector<float>> matrix;
	std::ifstream matrixFile(argv[1]);

	matrix = InitMatrix(matrixFile);

	bool zeroDeterminant = false;
	std::vector<std::vector<float>> inverseMatrix = FindInverseMatrix(matrix, zeroDeterminant);

	if (zeroDeterminant)
	{
		std::cout << "There is no inverse matrix, since the determinant is zero" << std::endl;
	}
	else
	{
		PrintMatrix(inverseMatrix);
	}

	return 0;
}