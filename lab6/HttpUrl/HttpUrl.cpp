#include "pch.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

void ParseURL(std::string const& url, HttpUrl::Protocol& protocol, HttpUrl::Port& port, std::string& host, std::string& document);
bool IsValidDomain(const std::string& domain);

HttpUrl::HttpUrl(std::string const& url)
{
	Protocol protocol;
	Port port;
	std::string domain;
	std::string document;
	try
	{
		ParseURL(url, protocol, port, domain, document);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;

		throw UrlParsingError("Can't construct invalid url object");
	}

	if (!IsValidDomain(domain))
	{
		throw UrlParsingError("Invalid domain value");
	}

	m_document = PreformatDocument(document);
	m_domain = domain;
	m_port = port;
	m_protocol = protocol;
}

HttpUrl::HttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
	Port port = GetDefaultPort(protocol);
	if (port == DEFAULT_NO_PORT)
	{
		throw UrlParsingError("Invalid protocol with no default port");
	}

	if (!IsValidDomain(domain))
	{
		throw UrlParsingError("Invalid domain value");
	}

	m_protocol = protocol;
	m_port = port;
	m_document = PreformatDocument(document);
	m_domain = domain;
}

HttpUrl::HttpUrl(std::string const& domain, std::string const& document, Protocol protocol, Port port)
{
	if (port > MAX_PORT || port < MIN_PORT)
	{
		throw UrlParsingError("Invalid port is out of range");
	}

	if (!IsValidDomain(domain))
	{
		throw UrlParsingError("Invalid domain value");
	}

	m_protocol = protocol;
	m_port = port;
	m_document = PreformatDocument(document);
	m_domain = domain;
}

std::string HttpUrl::GetURL() const
{
	std::string resultUrl;
	resultUrl += m_protocol == Protocol::HTTP ? "http" : "https";
	resultUrl += "://";
	resultUrl += m_domain;
	
	if (m_port != GetDefaultPort(m_protocol))
	{
		resultUrl += ":";
		resultUrl += m_port;
	}

	resultUrl += m_document;

	return resultUrl;
}

std::string HttpUrl::GetDomain() const
{
	return m_domain;
}

std::string HttpUrl::GetDocument() const
{
	return m_document;
}

HttpUrl::Protocol HttpUrl::GetProtocol() const
{
	return m_protocol;
}

HttpUrl::Port HttpUrl::GetPort() const
{
	return m_port;
}

HttpUrl::Protocol ParseProtocol(const std::string& protocolName)
{
	std::string protocol = TextToLower(protocolName);

	if (protocol == "http")
	{
		return HttpUrl::Protocol::HTTP;
	}
	else if (protocol == "https")
	{
		return HttpUrl::Protocol::HTTPS;
	}
	
	throw UrlParsingError("Invalid protocol value");
}

HttpUrl::Port ParsePort(const HttpUrl::Protocol& protocol, const std::string& port)
{
	if (port.empty())
	{
		return GetDefaultPort(protocol);
	}

	int portNumber;
	try
	{
		portNumber = std::stoi(port);
	}
	catch (...)
	{
		throw UrlParsingError("Invalid port value");
	}

	if (portNumber < HttpUrl::MIN_PORT || portNumber > HttpUrl::MAX_PORT)
	{
		throw UrlParsingError("Port value out of range");
	}

	return portNumber;
}

bool IsValidDomain(const std::string& domain)
{
	return domain.length() < 63;
}

std::string TextToLower(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(),
		[](char c) { return std::tolower(c); });

	return result;
}

HttpUrl::Port GetDefaultPort(const HttpUrl::Protocol& protocol)
{
	switch (protocol)
	{
	case HttpUrl::Protocol::HTTP:
		return HttpUrl::DEFAULT_HTTP_PORT;
	case HttpUrl::Protocol::HTTPS:
		return HttpUrl::DEFAULT_HTTPS_PORT;
	}

	return HttpUrl::DEFAULT_NO_PORT;
}

std::string PreformatDocument(std::string const& document)
{
	// FIXED: упростить
	std::string tempDocument = document;
	if (document[0] != '/')
	{
		tempDocument.insert(0, 1, '/');
	}

	return tempDocument;
}

void ParseURL(std::string const& url, HttpUrl::Protocol& protocol, HttpUrl::Port& port, std::string& host, std::string& document)
{
	std::regex preIpRegex(R"((https?)://(\d{1,}\.\d{1,}\.\d{1,}\.\d{1,})(?::(\d+))?(?:/(.{0,}))?)");
	std::regex ipRegex(R"((https?)://((?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?))(?::(\d+))?(?:/(.{0,}))?)");
	std::regex urlRegex(R"((https?)://([\w\-\.]+)(?::(\d+))?(?:/(.{0,}))?)");
	std::smatch result;

	std::string reformatUrl = TextToLower(url);

	if (std::regex_match(reformatUrl, result, preIpRegex))
	{
		if (!std::regex_match(reformatUrl, result, ipRegex))
		{
			throw UrlParsingError("Invalid ip value");
		}
	}
	else if (!std::regex_match(reformatUrl, result, urlRegex))
	{
		throw UrlParsingError("Invalid url value");
	}

	protocol = ParseProtocol(result[1].str());
	host = result[2].str();
	port = ParsePort(protocol, result[3].str());
	document = result[4].str();

	return;
}
