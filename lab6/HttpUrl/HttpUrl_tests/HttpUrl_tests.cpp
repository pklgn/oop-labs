#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HttpUrl.h"
#include <sstream>

SCENARIO("Constructing a correct URL")
{
	std::string url;

	WHEN("Given http URL contains document section without port")
	{
		url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		HttpUrl httpUrl = HttpUrl(url);
		THEN("Port will be equal to default port according to the protocol of the url")
		{
			REQUIRE(httpUrl.GetPort() == 80);
		}
		THEN("Evaluated protocol will be equal to http")
		{
			REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTP);
		}
		THEN("Document section will not be empty")
		{
			REQUIRE(httpUrl.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
		}
		THEN("Domain will be www.mysite.com")
		{
			REQUIRE(httpUrl.GetDomain() == "www.mysite.com");
		}
	}

	WHEN("Given https URL contains document section without port")
	{
		url = "https://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		HttpUrl httpUrl = HttpUrl(url);
		THEN("Port will be equal to default port according to the protocol of the url")
		{
			REQUIRE(httpUrl.GetPort() == 443);
		}
	}

	WHEN("Given https URL contains port without document")
	{
		url = "https://www.mysite.com:442";
		HttpUrl httpUrl = HttpUrl(url);
		THEN("Port will be equal to given port")
		{
			REQUIRE(httpUrl.GetPort() == 442);
		}
		THEN("Document section will be empty")
		{
			REQUIRE(httpUrl.GetDocument() == "/");
		}
	}

	WHEN("Given ftp URL contains port and document")
	{
		url = "http://www.mysite.com:442/docs/document1.html?page=30&lang=en#title";
		HttpUrl httpUrl = HttpUrl(url);
		THEN("Port will be equal to given port")
		{
			REQUIRE(httpUrl.GetPort() == 442);
		}
		THEN("Document section will not be empty")
		{
			REQUIRE(httpUrl.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
		}
	}

	WHEN("Given URL without domain, i.e. localhost that also has proper port value")
	{
		url = "http://localhost:42";
		HttpUrl httpUrl = HttpUrl(url);

		THEN("ParseURL will work correctly")
		{
			REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTP);
			REQUIRE(httpUrl.GetPort() == 42);
			REQUIRE(httpUrl.GetDomain() == "localhost");
		}
	}

	WHEN("Given URL without domain, i.e. localhost")
	{
		url = "http://localhost";
		HttpUrl httpUrl = HttpUrl(url);

		REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTP);
		REQUIRE(httpUrl.GetPort() == HttpUrl::DEFAULT_HTTP_PORT);
		REQUIRE(httpUrl.GetDomain() == "localhost");
	}
}

SCENARIO("Reading incorrect input data")
{
	std::string url;

	WHEN("Given a valid URL with invalid port")
	{
		url = "https://www.mysite.com:0/docs/document1.html?page=30&lang=en#title";
		REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
	}

	WHEN("Given a wrong protocol")
	{
		url = "ftp://www.mysite.com:0/docs/document1.html?page=30&lang=en#title";
		REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
	}

	WHEN("Given URL without domain, i.e. localhost that doesn't have proper port value")
	{
		url = "http://localhost:";
		REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
	}

	WHEN("Given URL without domain, i.e. localhost that also has invalid port value")
	{
		url = "http://localhost:0";
		THEN("ParseURL will return false")
		{
			REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
		}
		url = "http://localhost:-1";
		THEN("ParseURL will return false")
		{
			REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
		}
		url = "http://localhost:3424938493984";
		THEN("ParseURL will return false")
		{
			REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
		}
	}
}