#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

std::string ReplaceString(std::string& currString,
	const std::string& searchString, const std::string& replaceString)
{
	if (searchString.length() == 0)
	{
		return currString;
	}

	std::string result = "";
	while (currString.length() > 0)
	{
		const auto iterator = std::search(currString.begin(), currString.end(), searchString.begin(), searchString.end());
		const auto currPos = iterator - currString.begin();
		if (currPos == currString.length())
		{
			result.append(currString);
			currString.erase(currString.begin(), currString.end());
		}
		else
		{
			result.append(currString, 0, currPos);
			result.append(replaceString);
			currString.erase(currString.begin(), currString.begin() + currPos + searchString.length());
		}
	}

	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replaceString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replaceString) << "\n";
	}
}

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage replace.exe <input file> <output file> <search string> <replace string>";
		return 1;
	}

	std::ifstream sourceFile(argv[1]);
	if (!sourceFile.is_open())
	{
		std::cout << "Failed to open " << argv[1] << " for reading\n";

		return 1;
	}

	std::ofstream outputFile(argv[2]);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to open " << argv[2] << " for writing\n";

		return 1;
	}

	std::string searchString = argv[3];
	std::string replaceString = argv[4];

	CopyStreamWithReplacement(sourceFile, outputFile, searchString, replaceString);

	if (!outputFile.flush()) // Если не удалось сбросить данные на диск
	{
		std::cout << "Failed to save data on disk\n";

		return 1;
	}

	return 0;
}