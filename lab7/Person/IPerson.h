#pragma once
#include "pch.h"

class IPerson
{
public:
	virtual ~IPerson() = default;

	virtual std::string GetName() const = 0;
	virtual std::string GetSurname() const = 0;
	virtual std::string GetPatronymic() const = 0;
	virtual std::string GetAddress() const = 0;

	virtual void SetName(std::string const& name) = 0;
	virtual void SetSurname(std::string const& surname) = 0;
	virtual void SetPatronymic(std::string const& patronymic) = 0;
	virtual void SetAddress(std::string const& address) = 0;
};