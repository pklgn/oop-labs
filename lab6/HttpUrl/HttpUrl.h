#pragma once
#include "pch.h"

class HttpUrl
{
public:
	using Port = unsigned short;

	static const Port DEFAULT_HTTP_PORT = 80;
	static const Port DEFAULT_HTTPS_PORT = 443;
	static const Port DEFAULT_NO_PORT = 0;
	static const Port MIN_PORT = 1;
	static const Port MAX_PORT = 65535;

	enum class Protocol
	{
		HTTP,
		HTTPS
	};

	// ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
	// ���������� ���������� CUrlParsingError, ���������� ��������� �������� ������
	HttpUrl(std::string const& url);

	/* �������������� URL �� ������ ���������� ����������.
		��� �������������� ������� ���������� ����������� ����������
		std::invalid_argument
		���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	HttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	/* �������������� URL �� ������ ���������� ����������.
		��� �������������� ������� ���������� ����������� ����������
		std::invalid_argument
		���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	HttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		Port port);

	// ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
	// ���������� ��������� (80 ��� http � 443 ��� https) � ��� ������
	// �� ������ ����������
	std::string GetURL() const;

	// ���������� �������� ���
	std::string GetDomain() const;

	/*
		���������� ��� ���������. �������:
			/
			/index.html
			/images/photo.jpg
	*/
	std::string GetDocument() const;

	// ���������� ��� ���������
	Protocol GetProtocol() const;

	// ���������� ����� �����
	Port GetPort() const;

private:
	Protocol ParseProtocol(const std::string& protocolName) const;
	Port ParsePort(const Protocol& protocol, const std::string& port) const;
	bool IsValidDomain(const std::string& domain) const;
	std::string TextToLower(const std::string& str) const;
	Port GetDefaultPort(const Protocol& protocol) const;
	std::string PreformatDocument(std::string const& domain) const;
	void ParseURL(std::string const& url, Protocol& protocol, Port& port, std::string& host, std::string& document) const;

	std::string m_domain;
	Protocol m_protocol;
	Port m_port;
	std::string m_document;
};
