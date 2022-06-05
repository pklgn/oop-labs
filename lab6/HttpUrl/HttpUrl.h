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

	// выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	HttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
		ѕри недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	HttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	/* инициализирует URL на основе переданных параметров.
		ѕри недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	HttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		Port port);

	// возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
	// выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
	// не должен включатьс€
	std::string GetURL() const;

	// возвращает доменное им€
	std::string GetDomain() const;

	/*
		¬озвращает им€ документа. ѕримеры:
			/
			/index.html
			/images/photo.jpg
	*/
	std::string GetDocument() const;

	// возвращает тип протокола
	Protocol GetProtocol() const;

	// возвращает номер порта
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
