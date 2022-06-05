#include "pch.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

HttpUrl::HttpUrl(std::string const& url)
{
	Protocol protocol;
	Port port;
	std::string domain;
	std::string document;
	try
	{
		ParseURL(url, protocol, port, domain, document);
		m_document = PreformatDocument(document);
		m_domain = domain;
		m_port = port;
		m_protocol = protocol;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;

		throw UrlParsingError("Can't construct invalid url object");
	}
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

HttpUrl::Protocol HttpUrl::ParseProtocol(const std::string& protocolName) const
{
	std::string protocol = TextToLower(protocolName);

	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocol == "https")
	{
		return Protocol::HTTPS;
	}
	
	throw UrlParsingError("Invalid protocol value");
}

HttpUrl::Port HttpUrl::ParsePort(const Protocol& protocol, const std::string& port) const
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

	if (portNumber < MIN_PORT || portNumber >= MAX_PORT)
	{
		throw UrlParsingError("Port value out of range");
	}

	return portNumber;
}

bool HttpUrl::IsValidDomain(const std::string& domain) const
{
	return domain.length() > 63;
}

std::string HttpUrl::TextToLower(const std::string& str) const
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(),
		[](char c) { return std::tolower(c); });

	return result;
}

HttpUrl::Port HttpUrl::GetDefaultPort(const Protocol& protocol) const
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return DEFAULT_HTTP_PORT;
	case Protocol::HTTPS:
		return DEFAULT_HTTPS_PORT;
	}

	return DEFAULT_NO_PORT;
}

std::string HttpUrl::PreformatDocument(std::string const& document) const
{
	std::regex documentRegex(R"(^[\/][a-zA-Z0-9.,$;]{0,}$)");
	std::smatch result;

	std::string tempDocument = document;
	if (!std::regex_match(document, result, documentRegex))
	{
		tempDocument.insert(0, 1, '/');
	}

	return tempDocument;
}

void HttpUrl::ParseURL(std::string const& url, Protocol& protocol, Port& port, std::string& host, std::string& document) const
{
	std::regex urlRegex(R"((https?)://([\w\-\.]+)(?::(\d+))?(?:/(.+))?)");
	std::smatch result;

	if (!std::regex_match(url, result, urlRegex))
	{
		throw UrlParsingError("Invalid Url value");
	}

	try
	{
		protocol = ParseProtocol(result[1].str());
		host = result[2].str();
		port = ParsePort(protocol, result[3].str());
		document = result[4].str();
	}
	catch (std::invalid_argument& e)
	{
		throw;
	}

	return;
}
