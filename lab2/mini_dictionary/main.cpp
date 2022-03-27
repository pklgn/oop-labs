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

enum class DictionaryMode
{
	Modified,
	Saved,
};

enum class SessionStatus
{
	Pending,
	Exit,
};

struct DictionarySession
{
	Dictionary dict;
	DictionaryMode mode;
	SessionStatus status;
};


std::string GetDictionaryFileName(int argc, char* argv[]);
bool InitDictionary(std::string dictFileName, Dictionary& dict);

bool StartDictionarySession(DictionarySession& dictSession, std::string& dictFileName)
{
	if (!InitDictionary(dictFileName, dictSession.dict))
	{
		return false;
	}
	dictSession.status = SessionStatus::Pending;
	dictSession.mode = DictionaryMode::Saved;


	return true;
}

void ProcessRequest(std::istream& inputStream, std::ostream& outputStrea, DictionarySession dictSession);

int main(int argc, char* argv[])
{
	std::string dictFileName = GetDictionaryFileName(argc, argv);

	DictionarySession dictSession;
	if (!StartDictionarySession(dictSession, dictFileName))
	{
		return 1;
	}

	while (dictSession.status == SessionStatus::Pending)
	{
		ProcessRequest(std::cin, std::cout, dictSession);
	}


	
	return 0;
}

void ProcessRequest(std::istream& inputStream, std::ostream& outputStrea, DictionarySession dictSession)
{
	return;
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

bool InitDictionary(std::string dictFileName, Dictionary& dict)
{
	if (dictFileName != DEFAULT_DICTIONARY_FILE_NAME)
	{
		std::ifstream dictFile(dictFileName);
		if (!ReadDictionary(dictFile, dict))
		{
			return false;
		}
	}

	return true;
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