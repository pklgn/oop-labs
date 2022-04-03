#pragma once
#include <string>
#include <iostream>

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

std::string TextToLower(const std::string& str);

int GetDefaultPort(Protocol& protocol);

void PrintURL(std::string const& url, int& port, std::string& host, std::string& document,
	std::ostream& outputStream);

void ProcessURLParsing(std::istream& inputStream, std::ostream& outputStream);

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);