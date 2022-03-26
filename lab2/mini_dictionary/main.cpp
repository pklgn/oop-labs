#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string>

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

void ReadDictionary(std::ifstream& dictFile, Dictionary& dict);

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

void ReadTranslation(std::ifstream& dictFile, Dictionary& dict, std::string& term)
{

}

void ReadDictionary(std::ifstream& dictFile, Dictionary& dict)
{
	while (!dictFile.eof())
	{
		std::string term;
		std::getline(dictFile, term);
		RemoveExtraBlanks(term);
		ReadTranslation(dictFile, dict, term);
	}
}
