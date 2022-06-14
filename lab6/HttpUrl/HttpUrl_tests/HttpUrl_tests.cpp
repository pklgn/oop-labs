#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HttpUrl.h"
#include <sstream>

SCENARIO("Constructing a correct URL")
{
	std::string url;

	WHEN("Different register with http protocol")
	{
		url = "htTp://www.mysite.com/docs/document1.html?page=30&lang=en#title";

		THEN("With no throw")
		{
			REQUIRE_NOTHROW(HttpUrl(url));
		}
	}

	WHEN("Different register with https protocol")
	{
		url = "htTpS://www.mYsite.com/dOcs/document1.html?page=30&lang=en#title";
		HttpUrl httpUrl = HttpUrl(url);

		THEN("Will be default https protocol port")
		{
			REQUIRE(httpUrl.GetPort() == 443);
		}
		THEN("Protocol will be https")
		{
			REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTPS);
		}
		THEN("Domain will be mysite.com")
		{
			REQUIRE(httpUrl.GetDomain() == "www.mysite.com");
		}
	}

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

	WHEN("Given url with / is a document")
	{
		url = "https://google.com/";

		HttpUrl httpUrl = HttpUrl(url);

		REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTPS);
		REQUIRE(httpUrl.GetPort() == HttpUrl::DEFAULT_HTTPS_PORT);
		REQUIRE(httpUrl.GetDomain() == "google.com");
		REQUIRE(httpUrl.GetDocument() == "/");
	}
}

SCENARIO("Construct url using constructor with separate params")
{
	std::string url;
	std::string domain;
	std::string document;
	HttpUrl::Protocol protocol;

	WHEN("Given http URL contains document section without port")
	{
		url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		domain = "www.mysite.com";
		document = "docs/document1.html?page=30&lang=en#title";
		protocol = HttpUrl::Protocol::HTTP;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol);
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
		domain = "www.mysite.com";
		document = "docs/document1.html?page=30&lang=en#title";
		protocol = HttpUrl::Protocol::HTTPS;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol);
		THEN("Port will be equal to default port according to the protocol of the url")
		{
			REQUIRE(httpUrl.GetPort() == 443);
		}
	}

	WHEN("Given https URL contains port without document")
	{
		url = "https://www.mysite.com:442";
		domain = "www.mysite.com:442";
		document = "";
		protocol = HttpUrl::Protocol::HTTP;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol);
		THEN("Port will be equal to given port")
		{
			REQUIRE(httpUrl.GetPort() == 80);
		}
		THEN("Document section will be empty")
		{
			REQUIRE(httpUrl.GetDocument() == "/");
		}
	}

	WHEN("Given http URL contains port and document")
	{
		url = "http://www.mysite.com:442/docs/document1.html?page=30&lang=en#title";
		domain = "www.mysite.com:442";
		document = "docs/document1.html?page=30&lang=en#title";
		protocol = HttpUrl::Protocol::HTTP;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol);
		THEN("Port will be equal to given port")
		{
			REQUIRE(httpUrl.GetPort() == 80);
		}
		THEN("Document section will not be empty")
		{
			REQUIRE(httpUrl.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
		}
	}

	WHEN("Given URL without domain, i.e. localhost that also has proper port value")
	{
		url = "http://localhost:42";
		domain = "localhost:42";
		document = "";
		protocol = HttpUrl::Protocol::HTTP;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol);

		THEN("ParseURL will work correctly")
		{
			REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTP);
			REQUIRE(httpUrl.GetPort() == 80);
			REQUIRE(httpUrl.GetDomain() == "localhost:42");
		}
	}

	WHEN("Given URL without domain, i.e. localhost")
	{
		url = "http://localhost";
		domain = "localhost";
		document = "";
		protocol = HttpUrl::Protocol::HTTP;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol);

		REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTP);
		REQUIRE(httpUrl.GetPort() == HttpUrl::DEFAULT_HTTP_PORT);
		REQUIRE(httpUrl.GetDomain() == "localhost");
	}
}

SCENARIO("Construct url using constructor with all separate params")
{
	std::string url;
	std::string domain;
	std::string document;
	HttpUrl::Protocol protocol;
	HttpUrl::Port port;

	WHEN("Given http URL contains document section without port")
	{
		url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		domain = "www.mysite.com";
		document = "docs/document1.html?page=30&lang=en#title";
		protocol = HttpUrl::Protocol::HTTP;
		port = 80;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol, port);
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
		domain = "www.mysite.com";
		document = "docs/document1.html?page=30&lang=en#title";
		protocol = HttpUrl::Protocol::HTTPS;
		port = 443;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol, port);
		THEN("Port will be equal to default port according to the protocol of the url")
		{
			REQUIRE(httpUrl.GetPort() == 443);
		}
	}

	WHEN("Given https URL contains port without document")
	{
		url = "https://www.mysite.com:442";
		domain = "www.mysite.com";
		document = "";
		protocol = HttpUrl::Protocol::HTTP;
		port = 442;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol, port);
		THEN("Port will be equal to given port")
		{
			REQUIRE(httpUrl.GetPort() == 442);
		}
		THEN("Document section will be empty")
		{
			REQUIRE(httpUrl.GetDocument() == "/");
		}
	}

	WHEN("Given http URL contains port and document")
	{
		url = "http://www.mysite.com:442/docs/document1.html?page=30&lang=en#title";
		domain = "www.mysite.com";
		document = "docs/document1.html?page=30&lang=en#title";
		protocol = HttpUrl::Protocol::HTTP;
		port = 442;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol, port);
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
		domain = "localhost";
		document = "";
		protocol = HttpUrl::Protocol::HTTP;
		port = 42;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol, port);

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
		domain = "localhost";
		document = "";
		protocol = HttpUrl::Protocol::HTTP;
		port = 80;

		HttpUrl httpUrl = HttpUrl(domain, document, protocol, port);

		REQUIRE(httpUrl.GetProtocol() == HttpUrl::Protocol::HTTP);
		REQUIRE(httpUrl.GetPort() == HttpUrl::DEFAULT_HTTP_PORT);
		REQUIRE(httpUrl.GetDomain() == "localhost");
	}

	WHEN("Border cases")
	{
		url = "https://www.mysite.com:65535/docs/document1.html?page=30&lang=en#title";
		REQUIRE_NOTHROW(HttpUrl(url));
	}

}

SCENARIO("Reading incorrect input data")
{
	std::string url;

	WHEN("Border cases")
	{
		url = "https://www.mysite.com:65536/docs/document1.html?page=30&lang=en#title";
		REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
	}

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
		THEN("ParseURL will return exception")
		{
			REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
		}
		url = "http://localhost:-1";
		THEN("ParseURL will return exception")
		{
			REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
		}
		url = "http://localhost:3424938493984";
		THEN("ParseURL will return exception")
		{
			REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
		}
	}
	WHEN("Url port is bigger than port max value")
	{
		url = "http://localhost:65537";
		THEN("HttpUrl return an exception")
		{
			REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
		}
	}
	WHEN("Url also contain invalid document")
	{
		url = "http://localhost:65537/@#$sdljhfjshfkjdhsdf!&**_=;kjsdhf";
		THEN("HttpUrl return an exception")
		{
			REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
		}
	}
	WHEN("Url contain a very long domain value")
	{
		url = "http://verylongverylongverylongverylongverylongverylongverylongverylongverylongverylongverylongverylongverylongverylongverylongverylongverylongverylong:32/";
		THEN("HttpUrl return an exception")
		{
			REQUIRE_THROWS_AS(HttpUrl(url), std::invalid_argument);
		}
	}
}