#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

constexpr int FTP_PORT_DEFAULT = 21;
constexpr int HTTP_PORT_DEFAULT = 80;
constexpr int HTTPS_PORT_DEFAULT = 443;
constexpr int NO_PORT_DEFAULT = 0;
constexpr int MIN_PORT = 1;
constexpr int MAX_PORT = 65535;

Protocol ParseProtocol(const std::string& protocol);
int ParsePort(Protocol& protocol, const std::string& port);

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	bool isCorrect = true;
	std::regex regexURL(R"((https?|ftp)://([\w\-\.]+\.[\w]+):?(\d+)?/?(.+)?$)");
	std::cmatch result;

	if (!std::regex_match(url.c_str(), result, regexURL))
	{
		return !isCorrect;
	}
	protocol = ParseProtocol(result[1].str());
	host = result[2].str();
	port = ParsePort(protocol, result[3].str());
	document = result[3].str();

	return isCorrect;
}

std::string TextToLower(const std::string& str)
{
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) { return std::tolower(c); });


	return result;
}

Protocol ParseProtocol(const std::string& protocolName)
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

	throw std::invalid_argument("can't match protocol name");
}

int GetDefaultPort(Protocol& protocol)
{
	switch (protocol)
	{
		case Protocol::FTP:
			return FTP_PORT_DEFAULT;
		case Protocol::HTTP:
			return HTTP_PORT_DEFAULT;
		case Protocol::HTTPS:
			return HTTPS_PORT_DEFAULT;
	}

	std::cout << "Can't match protocol and default port\n";

	return NO_PORT_DEFAULT;
}

int ParsePort(Protocol& protocol, const std::string& port)
{
	if (port.empty())
	{
		return GetDefaultPort(protocol);
	}

	int portNumber = std::stoi(port);

	if (portNumber < MIN_PORT || portNumber > MAX_PORT)
	{
		return NO_PORT_DEFAULT;
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

int main()
{
	bool isCorrect;
	std::string url;
	while (std::getline(std::cin, url))
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
			PrintURL(url, port, host, document, std::cout);
		}
	}

	return 0;
}