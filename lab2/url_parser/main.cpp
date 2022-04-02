#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

constexpr unsigned short FTP_PORT_DEFAULT = 21;
constexpr unsigned short HTTP_PORT_DEFAULT = 80;
constexpr unsigned short HTTPS_PORT_DEFAULT = 443;
constexpr unsigned short NO_PORT_DEFAULT = 0;

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	bool isCorrect = true;

	return isCorrect;
}

unsigned short GetDefaultPort(Protocol& protocol)
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

int main()
{
	return 0;
}