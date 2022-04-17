#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../mini_dictionary_lib/mini_dictionary_lib.h"

SCENARIO("Working without initial dictionary file")
{
	DictionarySession dictSession;
	dictSession.dictFileName = DEFAULT_DICTIONARY_FILE_NAME;
	dictSession.mode = DictionaryMode::New;
	StartDictionarySession(dictSession);
	WHEN("Inserting new translation")
	{
		std::string term = "car";
		std::istringstream inputStream("автомобиль\n");
		std::ostringstream outputStream;
		AddTranslations(inputStream, outputStream, term, dictSession);
		auto translations = GetTranslations(dictSession.tempDict, term);
		REQUIRE(translations.value() == "автомобиль");
	}

		WHEN("Inserting new translation with two meanings")
	{
		std::string term = "outside";
		std::istringstream inputStream("снаружи,   вне\n");
		std::ostringstream outputStream;
		AddTranslations(inputStream, outputStream, term, dictSession);
		auto translations = GetTranslations(dictSession.tempDict, term);
		// TODO: прежде чем использовать find проверить на end() REQUIRE
		REQUIRE(dictSession.tempDict.find(term)->second.size() == 2);
		REQUIRE(translations.value() == "вне, снаружи");
	}

	WHEN("Inserting new translation with several meanings")
	{
		std::string term = "zoom";
		std::istringstream inputStream("быстро двигаться , приближать, увеличиваться, пользоваться Zoom\n");
		std::ostringstream outputStream;
		AddTranslations(inputStream, outputStream, term, dictSession);
		auto translations = GetTranslations(dictSession.tempDict, term);
		REQUIRE(dictSession.tempDict.find(term)->second.size() == 4);
		REQUIRE(translations.value() == "быстро двигаться, пользоваться Zoom, приближать, увеличиваться");
	}

	WHEN("There is no translation")
	{
		std::string term = "translation";
		std::istringstream inputStream(" \n");
		std::ostringstream outputStream;
		AddTranslations(inputStream, outputStream, term, dictSession);
		auto translations = GetTranslations(dictSession.tempDict, term);
		CHECK(!translations.has_value());
	}
}