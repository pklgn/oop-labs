#include "pch.h"
#include "string_format.h"

std::string CollapseExtraBlanks(const std::string& input)
{
	std::string result;
	unique_copy(input.begin(), input.end(), std::back_inserter(result),
		[](char a, char b) { return (a == ' ' && b == ' '); });
	
	return result;
}

std::string Trim(const std::string& str)
{
	const std::string WHITESPACE = " ";

	const auto stringBegin = str.find_first_not_of(WHITESPACE);
	if (stringBegin == std::string::npos)
	{
		return "";
	}

	const auto stringEnd = str.find_last_not_of(WHITESPACE);
	const auto stringRange = stringEnd - stringBegin + 1;

	return str.substr(stringBegin, stringRange);
}

std::string RemoveExtraBlanks(const std::string& string)
{
	std::string result = Trim(string);
	if (result.size() < 3)
	{
		return result;
	}

	return CollapseExtraBlanks(result);
}

std::set<std::string> SplitString(const std::string& string, char delimeter)
{
	std::string line;
	std::set<std::string> result;
	std::stringstream ss(string);
	while (std::getline(ss, line, delimeter))
	{
		line = RemoveExtraBlanks(line);
		if (!line.empty())
		{
			result.insert(line);
		}
	}

	return result;
}