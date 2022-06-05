#pragma once
#include "pch.h"
#include <stdexcept>

class UrlParsingError : public std::invalid_argument
{
public:
	explicit UrlParsingError(const std::string& message);
};
