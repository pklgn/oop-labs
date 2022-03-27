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

void RemoveExtraBlanks(std::string& term);

std::set<std::string> SplitString(std::string& string, char delimeter)
{
	std::string line;
	std::set<std::string> result;
	std::stringstream ss(string);
	while (std::getline(ss, line, delimeter))
	{
		result.insert(line);
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

	std::string rawTranslation;
	std::getline(dictFile, rawTranslation);
	auto translation = SplitString(rawTranslation, TRANSLATION_DELIMETER);
	std::for_each(translation.begin(), translation.end(), [&](std::string string) { RemoveExtraBlanks(string); });
	dict.emplace(term, translation);

	return true;
}

bool ReadDictionary(std::ifstream& dictFile, Dictionary& dict)
{
	while (!dictFile.eof())
	{
		std::string term;
		std::getline(dictFile, term);
		RemoveExtraBlanks(term);
		if (!ReadTranslation(dictFile, dict, term))
		{
			return false;
		}
	}

	return true;
}

void RemoveExtraBlanks(std::string& string)
{
	return;
}
