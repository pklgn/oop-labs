#pragma once
#include "pch.h"
#include "IPerson.h"

class IPupil : public IPerson
{
public:
	virtual ~IPupil();

	virtual std::string GetSchoolName() const = 0;
	virtual std::string GetClassName() const = 0;

	virtual void SetSchoolName(std::string const& schoolName) = 0;
	virtual void SetClassName(std::string const& className) = 0;
};