// mini_dictionary_lib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "string_format.h"
#include "mini_dictionary_lib.h"
// TODO: создавать и потом открывать dictionary.txt по умолчанию
// TODO: SetConsoleOutputCP();
// TODO: придумать способ, чтобы разделителем тоже были слова
const char DICTIONARY_DELIMETER = '-';
const std::string EXIT_COMMAND = "...";
const std::string OUTPUT_TRANSLATION_DELIMETER = ", ";

typedef std::map<std::string, std::set<std::string>> Dictionary;

bool HandleDictionarySession(std::string& dictFileName, std::istream& inputStream,
	std::ostream& outputStream)
{
	DictionarySession dictSession;
	dictSession.dictFileName = dictFileName;
	if (!StartDictionarySession(dictSession))
	{
		outputStream << dictSession.errorDescription << std::endl;
		return false;
	}

	while (dictSession.status == SessionStatus::Pending)
	{
		ProcessDictionarySession(inputStream, outputStream, dictSession);
	}

	return true;
}

std::string GetDictionaryFileName(int argc, char ** argv)
{
	if (argc == 1)
	{
		return DEFAULT_DICTIONARY_FILE_NAME;
	}

	return argv[1];
}

void SetDictionaryMode(DictionaryMode& dictMode, std::ifstream& dictFile)
{
	if (!dictFile.good())
	{
		dictMode = DictionaryMode::New;

		return;
	}

	dictMode = DictionaryMode::Saved;

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
	if (request == EXIT_COMMAND || inputStream.eof())
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

void FinishDictionarySession(std::istream& inputStream, std::ostream& outputStream, DictionarySession& dictSession)
{
	dictSession.status = SessionStatus::Exit;

	if (dictSession.mode == DictionaryMode::Modified)
	{
		if (inputStream.eof())
		{
			outputStream << "Последние изменения будут утеряны.\n";

			return;
		}

		outputStream << "В словарь были внесены изменения. "
						"Введите Y или y для сохранения перед выходом.\n";
		char response;
		inputStream >> response;
		if (std::tolower(response) == 'y')
		{
			SaveDictionarySession(dictSession);

			outputStream << "Изменения сохранены. ";
		}
	}
	
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
	std::stringstream outputTranslations;
	auto dictPair = dict.find(term);
	if (dictPair == dict.end())
	{
		return std::nullopt;
	}

	std::set<std::string> translations = dictPair->second;
	for (auto it = translations.begin(); it != translations.end(); it++)
	{
		outputTranslations << *it;
		if (std::distance(translations.begin(), it) != translations.size() - 1)
		{
			outputTranslations << OUTPUT_TRANSLATION_DELIMETER;
		}
	}

	return outputTranslations.str();
}

void AddTranslations(std::istream& inputStream, std::ostream& outputStream, const std::string& term,
	DictionarySession& dictSession)
{
	outputStream << "Неизвестное слово \"" << term << "\". Введите перевод или пустую строку для отказа.\n";
	if (!ReadTranslations(inputStream, dictSession.tempDict, term))
	{
		outputStream << "Слово \"" << term << "\" проигнорировано.\n";

		return;
	}
	dictSession.mode = DictionaryMode::Modified;
	outputStream << "Слово \"" << term << "\" сохранено в словаре как \""
				 << GetTranslations(dictSession.tempDict, term).value() << "\"\n";
}

bool InitDictionary(DictionarySession& dictSession)
{
	std::ifstream dictFile(dictSession.dictFileName);
	SetDictionaryMode(dictSession.mode, dictFile);

	if (dictSession.mode != DictionaryMode::New)
	{
		std::ifstream dictFile(dictSession.dictFileName);
		if (!dictFile.is_open())
		{
			dictSession.errorDescription = dictSession.dictFileName + " file can't be opened"; 

			return false;
		}

		if (!ReadDictionary(dictFile, dictSession.dict))
		{
			dictSession.errorDescription = "Can't read dictionary file";

			return false;
		}
	}

	return true;
}

bool ReadTranslations(std::istream& inputFile, Dictionary& dict, const std::string& term)
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
			return false;
		}
	}

	return true;
}
