#pragma once
#include <set>
#include <map>
#include <optional>
#include <iostream>

const std::string DEFAULT_DICTIONARY_FILE_NAME = "dictionary.txt";

typedef std::map<std::string, std::set<std::string>> Dictionary;

enum class DictionaryMode
{
	New,
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
	std::string errorDescription;
};


// TODO: не использовать argc, argv, пусть вернет имя в виде строки
std::string GetDictionaryFileName(int argc, char** argv);

bool HandleDictionarySession(std::string& dictFileName,
	std::istream& inputStream, std::ostream& outputStream);

bool StartDictionarySession(DictionarySession& dictSession);

void ProcessDictionarySession(std::istream& inputStream, std::ostream& outputStrea, DictionarySession& dictSession);

void SaveDictionarySession(DictionarySession& dictSession);

void FinishDictionarySession(std::istream& inputStream, std::ostream& outputStream, DictionarySession& dictSession);

bool InitDictionary(DictionarySession& dictSession);

bool ReadDictionary(std::ifstream& dictFile, Dictionary& dict);

std::optional<std::string> GetTranslations(Dictionary& dict, const std::string& term);

bool ReadTranslations(std::istream& inputFile, Dictionary& dict, const std::string & term);

void AddTranslations(std::istream& inputStream, std::ostream& outputStream, const std::string & term, DictionarySession& dictSession);