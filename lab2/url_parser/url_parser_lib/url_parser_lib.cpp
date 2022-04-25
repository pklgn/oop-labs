// url_parser_lib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "url_parser_lib.h"

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	// TODO: rename и вынести в const 
	std::regex URLregex(R"((https?|ftp)://([\w\-\.]+)(?::(\d+))?(?:/(.+))?)");
	std::smatch result;
	if (!std::regex_match(url, result, URLregex))
	{
		return false;
	}
	
	std::optional<Protocol> oProtocol = ParseProtocol(result[1].str());
	if (!oProtocol.has_value())
	{
		return false;
	}
	protocol = oProtocol.value();
	host = result[2].str();
	std::optional<int> oPort = ParsePort(protocol, result[3].str());
	if (!oPort.has_value())
	{
		return false;
	}
	port = oPort.value();
	document = result[4].str();

	return true;
}

std::string TextToLower(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(),
		[](char c) { return std::tolower(c); });

	return result;
}

std::optional<Protocol> ParseProtocol(const std::string& protocolName)
{
	std::string protocol = TextToLower(protocolName);

	if (protocol == "ftp")
	{
		return Protocol::FTP;
	}
	else if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	else if (protocol == "https")
	{
		return Protocol::HTTPS;
	}
	else
	{
		return std::nullopt;
	}
}

int GetDefaultPort(const Protocol& protocol)
{
	switch (protocol)
	{
	case Protocol::FTP:
		return DEFAULT_FTP_PORT;
	case Protocol::HTTP:
		return DEFAULT_HTTP_PORT;
	case Protocol::HTTPS:
		return DEFAULT_HTTPS_PORT;
	}
	// TODO: rename
	return DEFAULT_NO_PORT;
}

std::optional<int> ParsePort(const Protocol& protocol, const std::string& port)
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
		return std::nullopt;
	}
	// TODO: проверять границы
	if (portNumber < MIN_PORT || portNumber >= MAX_PORT)
	{
		return std::nullopt;
	}

	return portNumber;
}

void PrintURL(std::string const& url, int& port, std::string& host, std::string& document,
	std::ostream& outputStream)
{
	outputStream << url << std::endl
				 << "HOST: " << host << std::endl
				 << "PORT: " << port << std::endl
				 << "DOC: " << document << std::endl;
}

void ProcessURLParsing(std::istream& inputStream, std::ostream& outputStream)
{
	bool isCorrect;
	std::string url;
	while (std::getline(inputStream, url))
	{
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		isCorrect = ParseURL(url, protocol, port, host, document);

		if (!isCorrect)
		{
			std::cout << "Can't parse url " << url << std::endl;
		}
		else
		{
			PrintURL(url, port, host, document, outputStream);
		}
	}

	return;
}