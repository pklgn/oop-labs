#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <optional>

const char DICTIONARY_DELIMETER = '-';
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
	Inactive,
	Pending,
	Exit,
};

struct DictionarySession
{
	Dictionary dict;
	Dictionary tempDict;
	DictionaryMode mode = DictionaryMode::Saved;
	SessionStatus status = SessionStatus::Inactive;
	std::string dictFileName;
};

void SetDictionaryFileName(int argc, char* argv[], DictionarySession& dictSession);
bool InitDictionary(DictionarySession& dictSession);
bool StartDictionarySession(DictionarySession& dictSession);
void ProcessDictionarySession(std::istream& inputStream, std::ostream& outputStrea, DictionarySession& dictSession);

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	DictionarySession dictSession;
	SetDictionaryFileName(argc, argv, dictSession);

	if (!StartDictionarySession(dictSession))
	{
		return 1;
	}

	while (dictSession.status == SessionStatus::Pending)
	{
		ProcessDictionarySession(std::cin, std::cout, dictSession);
	}
	
	return 0;
}

void SetDictionaryFileName(int argc, char* argv[], DictionarySession& dictSession)
{
	if (argc == 1)
	{
		dictSession.dictFileName = DEFAULT_DICTIONARY_FILE_NAME;
	}

	dictSession.dictFileName = argv[1];
}

bool StartDictionarySession(DictionarySession& dictSession)
{
	if (!InitDictionary(dictSession))
	{
		return false;
	}
	dictSession.mode = DictionaryMode::Saved;
	dictSession.status = SessionStatus::Pending;

	return true;
}

std::string RemoveExtraBlanks(const std::string& string);
std::optional<std::string> GetTranslations(Dictionary& dict, const std::string& term);
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
			outputStream << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
			char response;
			inputStream >> response;
			if (response == 'Y' || response == 'y')
			{
				std::ofstream dictFile(dictSession.dictFileName, std::ios::app);
				for (const auto& [term, translations]: dictSession.tempDict)
				{
					dictFile << term << DICTIONARY_DELIMETER
							 << GetTranslations(dictSession.tempDict, term).value() << std::endl;
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
	auto dictTranslations = GetTranslations(dictSession.dict, request);
	auto tempDictTranslations = GetTranslations(dictSession.tempDict, request);
	if (!dictTranslations.has_value() && !tempDictTranslations.has_value())
	{
		AddTranslation(inputStream, outputStream, request, dictSession);
	}
	else if (dictTranslations.has_value())
	{
		outputStream << dictTranslations.value() << std::endl;
	}
	else 
	{
		outputStream << tempDictTranslations.value() << std::endl;
	}
}

std::optional<std::string> GetTranslations(Dictionary& dict, const std::string& term)
{
	std::stringstream rawTranslations;
	auto it = dict.find(term);
	if (it == dict.end())
	{
		return std::nullopt;
	}
	std::set<std::string> translations = it->second;
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
	outputStream << "Неизвестное слово \"" << term << "\". Введите перевод или пустую строку для отказа.\n";
	if (!ReadTranslation(inputStream, dictSession.tempDict, term))
	{
		outputStream << "Слово \"" << term << "\" проигнорировано.\n";

		return;
	}
	dictSession.mode = DictionaryMode::Modified;
	outputStream << "Слово \"" << term << "\" сохранено в словаре как \"" << GetTranslations(dictSession.tempDict, term).value() << "\"\n";
}

bool ReadDictionary(std::ifstream& dictFile, Dictionary& dict);

bool InitDictionary(DictionarySession& dictSession)
{
	if (dictSession.dictFileName != DEFAULT_DICTIONARY_FILE_NAME)
	{
		std::ifstream dictFile(dictSession.dictFileName);
		if (!ReadDictionary(dictFile, dictSession.dict))
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
	while (std::getline(dictFile, term, DICTIONARY_DELIMETER))
	{
		term = RemoveExtraBlanks(term);
		if (!ReadTranslation(dictFile, dict, term))
		{
			std::cout << "Fail to read translation for " << term << std::endl;

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