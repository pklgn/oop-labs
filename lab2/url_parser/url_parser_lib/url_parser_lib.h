#pragma once
#include <string>
#include <iostream>
#include <optional>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
};

constexpr int DEFAULT_FTP_PORT = 21;
constexpr int DEFAULT_HTTP_PORT = 80;
constexpr int DEFAULT_HTTPS_PORT = 443;
constexpr int DEFAULT_NO_PORT = 0;
constexpr int MIN_PORT = 1;
constexpr int MAX_PORT = 65535;

std::optional<Protocol> ParseProtocol(const std::string& protocolName);

std::optional<int> ParsePort(const Protocol& protocol, const std::string& port);

std::string TextToLower(const std::string& str);

int GetDefaultPort(Protocol& protocol);

void PrintURL(std::string const& url, int& port, std::string& host, std::string& document,
	std::ostream& outputStream);

void ProcessURLParsing(std::istream& inputStream, std::ostream& outputStream);

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);