#pragma once
#include "pch.h"
#include "IPerson.h"

class ITeacher : public IPerson
{
public:
	virtual ~ITeacher() = default;

	virtual std::string GetSubjectName() const = 0;

	virtual void SetSubjectName(std::string const& subjectName) = 0;
};