#pragma once
#include "pch.h"
#include "IPerson.h"

class IPupil : public IPerson
{
public:
	virtual ~IPupil() = default;

	virtual std::string GetSchoolName() const = 0;
	virtual std::string GetSchoolClass() const = 0;

	virtual void SetSchoolName(std::string const& schoolName) = 0;
	virtual void SetSchoolClass(std::string const& schoolClass) = 0;
};