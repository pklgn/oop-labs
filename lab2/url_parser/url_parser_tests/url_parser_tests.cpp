#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../url_parser_lib/url_parser_lib.h"
#include <sstream>

SCENARIO("Reading a correct URL")
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	std::string url;

	WHEN("Given http URL contains document section without port")
	{

		url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		ParseURL(url, protocol, port, host, document);
		THEN("Port will be equal to default port according to the protocol of the url")
		{
			REQUIRE(port == 80);
		}
		THEN("Evaluated protocol will be equal to http")
		{
			REQUIRE(protocol == Protocol::HTTP);
		}
		THEN("Document section will not be empty")
		{
			REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
		}
	}

	WHEN("Given https URL contains document section without port")
	{
		url = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		ParseURL(url, protocol, port, host, document);
		THEN("Port will be equal to default port according to the protocol of the url")
		{
			REQUIRE(port == 443);
		}
	}

	WHEN("Given ftp URL contains document section without port")
	{
		url = "ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		ParseURL(url, protocol, port, host, document);
		THEN("Port will be equal to default port according to the protocol of the url")
		{
			REQUIRE(port == 21);
		}
	}

	WHEN("Given https URL contains port without document")
	{
		url = "https://www.mysite.com:442";
		ParseURL(url, protocol, port, host, document);
		THEN("Port will be equal to given port")
		{
			REQUIRE(port == 442);
		}
		THEN("Document section will be empty")
		{
			REQUIRE(document.empty());
		}
	}

	WHEN("Given ftp URL contains port and document")
	{
		url = "ftp://www.mysite.com:442/docs/document1.html?page=30&lang=en#title";
		ParseURL(url, protocol, port, host, document);
		THEN("Port will be equal to given port")
		{
			REQUIRE(port == 442);
		}
		THEN("Document section will not be empty")
		{
			REQUIRE(document == "docs/document1.html?page=30&lang=en#title");
		}
	}
}

SCENARIO("Reading correct input stream")
{
	WHEN("Given a valid URL")
	{
		std::stringstream inputStream("ftp://www.mysite.com:442/docs/document1.html?page=30&lang=en#title");
		std::stringstream outputStream;
		ProcessURLParsing(inputStream, outputStream);
		REQUIRE(outputStream.str() == "ftp://www.mysite.com:442/docs/document1.html?page=30&lang=en#title\nHOST: www.mysite.com\nPORT: 442\nDOC: docs/document1.html?page=30&lang=en#title\n");
	}
}

SCENARIO("Reading incorrect input data")
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	std::string url;

	WHEN("Given a valid URL with invalid port")
	{
		url = "ftp://www.mysite.com:0/docs/document1.html?page=30&lang=en#title";
		bool isCorrect = ParseURL(url, protocol, port, host, document);
		REQUIRE(!isCorrect);
	}

	WHEN("Given a wrong protocol")
	{
		REQUIRE_THROWS(ParseProtocol("file"));
	}

	WHEN("Given URL is incorrect")
	{
		url = "ftp:/www.mysite.com:0/docs/document1.html?page=30&lang=en#title";
		bool isCorrect = ParseURL(url, protocol, port, host, document);
		REQUIRE(!isCorrect);
	}
}