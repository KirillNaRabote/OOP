#include "stdafx.h"

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString == "")
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;

	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		if (foundPos == std::string::npos)
		{
			foundPos = subject.length();
		}
		result.append(subject, pos, foundPos - pos);
		if (foundPos != subject.length())
		{
			result += replacementString;
		}
		pos = foundPos + searchString.length();
	}
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

int CopyFileWithReplacement(const std::string& inputFileName, const std::string& outputFileName,
	const std::string& searchString, const std::string& replacementString)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open " << inputFileName << " for reading\n";
		return 1;
	}

	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to open " << outputFileName << " for writing\n";
		return 1;
	}

	CopyStreamWithReplacement(inputFile, outputFile, searchString, replacementString);

	outputFile.flush();

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	return CopyFileWithReplacement(argv[1], argv[2], argv[3], argv[4]);
}