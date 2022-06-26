#pragma once
#include "pch.h"
#include "IPerson.h"

class IStudent : public IPerson
{
public:
	virtual ~IStudent() = default;

	virtual std::string GetUniversityName() const = 0;
	virtual std::string GetID() const = 0;

	virtual void SetUniversityName(std::string const& univesityName) = 0;
	virtual void SetID(std::string const& ID) = 0;
};