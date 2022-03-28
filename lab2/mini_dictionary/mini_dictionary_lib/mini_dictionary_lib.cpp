// mini_dictionary_lib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "mini_dictionary_lib.h"


const char DICTIONARY_DELIMETER = '-';
const std::string EXIT_COMMAND = "...";
const std::string RAW_TRANSLATION_DELIMETER = ", ";

typedef std::map<std::string, std::set<std::string>> Dictionary;

bool LaunchDictionarySession(int argc, char* argv[],
	std::istream& inputStream, std::ostream& outputStream)
{
	DictionarySession dictSession;
	SetDictionaryFileName(argc, argv, dictSession);
	if (!StartDictionarySession(dictSession))
	{
		return false;
	}

	while (dictSession.status == SessionStatus::Pending)
	{
		ProcessDictionarySession(inputStream, outputStream, dictSession);
	}

	return true;
}

void SetDictionaryFileName(int argc, char* argv[], DictionarySession& dictSession)
{
	if (argc == 1)
	{
		dictSession.dictFileName = DEFAULT_DICTIONARY_FILE_NAME;
		dictSession.mode = DictionaryMode::New;

		return;
	}
	dictSession.mode = DictionaryMode::Saved;
	dictSession.dictFileName = argv[1];

	return;
}

bool StartDictionarySession(DictionarySession& dictSession)
{
	if (!InitDictionary(dictSession))
	{
		return false;
	}
	dictSession.status = SessionStatus::Pending;

	return true;
}

void ProcessDictionarySession(std::istream& inputStream, std::ostream& outputStream, DictionarySession& dictSession)
{
	std::string request;
	std::getline(inputStream, request);
	request = RemoveExtraBlanks(request);
	if (request == EXIT_COMMAND)
	{
		FinishDictionarySession(inputStream, outputStream, dictSession);

		return;
	}

	auto translations = GetTranslations(dictSession.dict, request);
	auto tempTranslations = GetTranslations(dictSession.tempDict, request);
	if (translations.has_value())
	{
		outputStream << translations.value() << std::endl;
	}
	else if (tempTranslations.has_value())
	{
		outputStream << tempTranslations.value() << std::endl;
	}
	else
	{
		AddTranslations(inputStream, outputStream, request, dictSession);
	}
}
void SaveDictionarySession(DictionarySession& dictSession);
void FinishDictionarySession(std::istream& inputStream, std::ostream& outputStream, DictionarySession& dictSession)
{
	if (dictSession.mode == DictionaryMode::Modified)
	{
		outputStream << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
		std::string response;
		std::getline(inputStream, response);
		response = RemoveExtraBlanks(response);
		if (response == "Y" || response == "y")
		{
			SaveDictionarySession(dictSession);
			outputStream << "Изменения сохранены. ";
		}
	}
	dictSession.status = SessionStatus::Exit;
	outputStream << "До свидания.\n";

	return;
}

void SaveDictionarySession(DictionarySession& dictSession)
{
	std::ofstream dictFile(dictSession.dictFileName, std::ios::app);
	for (const auto& [term, translations] : dictSession.tempDict)
	{
		dictFile << term << DICTIONARY_DELIMETER
				 << GetTranslations(dictSession.tempDict, term).value() << std::endl;
	}

	if (!dictFile.flush())
	{
		std::cout << "Не удалось сохранить изменения на диске\n";
	}

	return;
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
			rawTranslations << RAW_TRANSLATION_DELIMETER;
		}
	}

	return rawTranslations.str();
}

void AddTranslations(std::istream& inputStream, std::ostream& outputStream, std::string& term,
	DictionarySession& dictSession)
{
	outputStream << "Неизвестное слово \"" << term
				 << "\". Введите перевод или пустую строку для отказа.\n";
	if (!ReadTranslations(inputStream, dictSession.tempDict, term))
	{
		outputStream << "Слово \"" << term << "\" проигнорировано.\n";

		return;
	}
	dictSession.mode = DictionaryMode::Modified;
	outputStream << "Слово \"" << term << "\" сохранено в словаре как \""
				 << GetTranslations(dictSession.tempDict, term).value() << "\"\n";
}

bool ReadDictionary(std::ifstream& dictFile, Dictionary& dict);
bool InitDictionary(DictionarySession& dictSession)
{
	if (!(dictSession.dictFileName == DEFAULT_DICTIONARY_FILE_NAME && dictSession.mode == DictionaryMode::New))
	{
		std::ifstream dictFile(dictSession.dictFileName);
		if (!dictFile.is_open())
		{
			std::cout << "Невозможно открыть файл " << dictSession.dictFileName << std::endl;

			return false;
		}

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
		line = RemoveExtraBlanks(line);
		if (!line.empty())
		{
			result.insert(line);
		}
	}

	return result;
}

bool ReadTranslations(std::istream& inputFile, Dictionary& dict, std::string& term)
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
		if (!ReadTranslations(dictFile, dict, term))
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
	return Trim(string);
}