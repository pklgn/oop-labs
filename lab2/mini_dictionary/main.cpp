#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

const std::string DEFAULT_DICTIONARY_FILE_NAME = "dictionary.txt";

typedef std::map<std::string, std::set<std::string>> Dictionary;

std::string GetDictionaryFileName(int argc, char* argv[]);
void InitDictionary(std::string dictFileName, Dictionary& dict);

int main(int argc, char* argv[])
{
	std::string dictFileName = GetDictionaryFileName(argc, argv);

	Dictionary dict;
	InitDictionary(dictFileName, dict);
	
}

std::string GetDictionaryFileName(int argc, char* argv[])
{
	if (argc == 1)
	{
		return DEFAULT_DICTIONARY_FILE_NAME;
	}
	
	return argv[1];
}

bool ReadDictionary(std::ifstream& dictFile, Dictionary& dict);

void InitDictionary(std::string dictFileName, Dictionary& dict)
{
	if (dictFileName != DEFAULT_DICTIONARY_FILE_NAME)
	{
		std::ifstream dictFile(dictFileName);
		ReadDictionary(dictFile, dict);
	}

	return;
}

std::string RemoveExtraBlanks(const std::string& string);

std::set<std::string> SplitString(std::string& string, char delimeter)
{
	std::string line;
	std::set<std::string> result;
	std::stringstream ss(string);
	while (std::getline(ss, line, delimeter))
	{
		result.insert(RemoveExtraBlanks(line));
	}
	
	return result;
}

bool ReadTranslation(std::ifstream& dictFile, Dictionary& dict, std::string& term)
{
	const char TRANSLATION_DELIMETER = ',';
	if (dictFile.eof())
	{
		std::cout << "Fail to read translation for " << term << std::endl;

		return false;
	}

	std::string rawTranslations;
	std::getline(dictFile, rawTranslations);
	auto translations = SplitString(rawTranslations, TRANSLATION_DELIMETER);
	dict.emplace(term, translations);

	return true;
}

bool ReadDictionary(std::ifstream& dictFile, Dictionary& dict)
{
	while (!dictFile.eof())
	{
		std::string term;
		std::getline(dictFile, term);
		term = RemoveExtraBlanks(term);
		if (!ReadTranslation(dictFile, dict, term))
		{
			return false;
		}
	}

	return true;
}

std::string Trim(const std::string& str)
{
	const std::string WHITESPACE = " ";
	const auto strBegin = str.find_first_not_of(WHITESPACE);
	if (strBegin == std::string::npos)
	{
		return "";
	}

	const auto strEnd = str.find_last_not_of(WHITESPACE);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

std::string RemoveExtraBlanks(const std::string& string)
{
	return Trim(string);
}