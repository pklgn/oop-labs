#pragma once
#include <iostream>
#include <set>
#include <map>
#include <optional>

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
};

bool LaunchDictionarySession(int argc, char* argv[],
	std::istream& inputStream, std::ostream& outputStream);

bool StartDictionarySession(DictionarySession& dictSession);

void SetDictionaryFileName(int argc, char* argv[], DictionarySession& dictSession);

bool InitDictionary(DictionarySession& dictSession);

void ProcessDictionarySession(std::istream& inputStream, std::ostream& outputStrea, DictionarySession& dictSession);

std::string RemoveExtraBlanks(const std::string& string);

std::optional<std::string> GetTranslations(Dictionary& dict, const std::string& term);

bool ReadTranslations(std::istream& inputFile, Dictionary& dict, std::string& term);

void AddTranslations(std::istream& inputStream, std::ostream& outputStream, std::string& term, DictionarySession& dictSession);

void FinishDictionarySession(std::istream& inputStream, std::ostream& outputStream, DictionarySession& dictSession);