#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

const std::string EXIT_COMMAND = "...";
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
	Dictionary tempDict;
	DictionaryMode mode;
	SessionStatus status;
	std::string dictFileName;
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

void ProcessDictionarySession(std::istream& inputStream, std::ostream& outputStrea, DictionarySession& dictSession);

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	std::string dictFileName = GetDictionaryFileName(argc, argv);

	DictionarySession dictSession;
	dictSession.dictFileName = dictFileName;
	if (!StartDictionarySession(dictSession, dictFileName))
	{
		return 1;
	}

	while (dictSession.status == SessionStatus::Pending)
	{
		ProcessDictionarySession(std::cin, std::cout, dictSession);
	}
	
	return 0;
}
std::string RemoveExtraBlanks(const std::string& string);
std::string GetTranslations(Dictionary& dict, const std::string& term);
bool ReadTranslation(std::istream& inputFile, Dictionary& dict, std::string& term);
void AddTranslation(std::istream& inputStream, std::ostream& outputStream, std::string& term, DictionarySession& dictSession);

void ProcessDictionarySession(std::istream& inputStream, std::ostream& outputStream, DictionarySession& dictSession)
{
	std::string request;
	std::getline(inputStream, request);
	request = RemoveExtraBlanks(request);
	if (request == EXIT_COMMAND)
	{
		if (dictSession.mode == DictionaryMode::Modified)
		{
			outputStream << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������.\n";
			char response;
			inputStream >> response;
			if (response == 'Y' || response == 'y')
			{
				std::ofstream dictFile(dictSession.dictFileName, std::ios::app);
				for (const auto& [term, translations]: dictSession.tempDict)
				{
					dictFile << term << '-'
							 << GetTranslations(dictSession.tempDict, term) << std::endl;
				}
				if (!dictFile.flush())
				{
					std::cout << "Can't save changes to file\n";
				}
			}
		}
		dictSession.status = SessionStatus::Exit;

		return;
	}
	auto it = dictSession.dict.find(request);
	if (it == dictSession.dict.end())
	{
		AddTranslation(inputStream, outputStream, request, dictSession);
	}
}

std::string GetTranslations(Dictionary& dict, const std::string& term)
{
	std::stringstream rawTranslations;
	std::set<std::string> translations = dict.find(term)->second;
	for (auto it = translations.begin(); it != translations.end(); it++)
	{
		rawTranslations << *it;
		if (std::distance(translations.begin(), it) != translations.size() - 1)
		{
			rawTranslations << ", ";
		}
	}

	return rawTranslations.str();
}

void AddTranslation(std::istream& inputStream, std::ostream& outputStream, std::string& term, DictionarySession& dictSession)
{
	outputStream << "����������� ����� \"" << term << "\". ������� ������� ��� ������ ������ ��� ������.\n";
	if (!ReadTranslation(inputStream, dictSession.tempDict, term))
	{
		outputStream << "����� \"" << term << "\" ���������������.\n";

		return;
	}
	dictSession.mode = DictionaryMode::Modified;
	outputStream << "����� \"" << term << "\" ��������� � ������� ��� \"" << GetTranslations(dictSession.tempDict, term) << "\"\n";
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

bool ReadTranslation(std::istream& inputFile, Dictionary& dict, std::string& term)
{
	const char TRANSLATION_DELIMETER = ',';
	if (inputFile.eof())
	{
		return false;
	}

	std::string rawTranslations;
	std::getline(inputFile, rawTranslations);
	auto translations = SplitString(rawTranslations, TRANSLATION_DELIMETER);
	if (translations.size() == 0)
	{
		return false;
	}
	dict.emplace(term, translations);

	return true;
}

bool ReadDictionary(std::ifstream& dictFile, Dictionary& dict)
{
	std::string term;
	while (std::getline(dictFile, term, '-'))
	{
		term = RemoveExtraBlanks(term);
		if (!ReadTranslation(dictFile, dict, term))
		{
			std::cout << "Fail to read translation for " << term << std::endl;

			return false;
		}
		if (dictFile.eof())
		{
			break;
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