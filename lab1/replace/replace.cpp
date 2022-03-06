#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <functional>
#include <optional>

std::string ReplaceString(std::string& currString,
	const std::string& searchString, const std::string& replaceString)
{
	if (searchString.length() == 0)
	{
		return currString;
	}

	size_t currPos = 0;
	std::string result;
	const auto searcher = std::boyer_moore_horspool_searcher(searchString.begin(), searchString.end());
	while (currPos < currString.length())
	{
		
		const auto it = std::search(currString.begin() + currPos, currString.end(), searcher);
		result.append(currString, currPos, it - currString.begin() - currPos);
		if (it == currString.end())
		{
			break;
		}
		else
		{
			result.append(replaceString);
			currPos += it - currString.begin() - currPos + searchString.length();
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
		output << ReplaceString(line, searchString, replaceString) << std::endl;
	}
}

struct Params
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

std::optional<Params> GetParams(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n"
			<< "Usage replace.exe <input file> <output file> <search string> <replace string>";
		return std::nullopt;
	}

	return { { argv[1], argv[2], argv[3], argv[4] } };
}

bool Replace(Params params)
{
	std::ifstream sourceFile(params.inputFileName);
	if (!sourceFile.is_open())
	{
		std::cout << "Failed to open " << params.inputFileName << " for reading\n";

		return false;
	}

	std::ofstream outputFile(params.outputFileName);
	if (!outputFile.is_open())
	{
		std::cout << "Failed to open " << params.outputFileName << " for writing\n";

		return false;
	}

	CopyStreamWithReplacement(sourceFile, outputFile, params.searchString, params.replaceString);

	if (!outputFile.flush()) // Если не удалось сбросить данные на диск
	{
		std::cout << "Failed to save data on disk\n";

		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	std::optional<Params> params = GetParams(argc, argv);
	if (!params.has_value())
	{
		return 1;
	}
	
	bool status = Replace(params.value());
	if (!status)
	{
		return 1;
	}

	return 0;
}