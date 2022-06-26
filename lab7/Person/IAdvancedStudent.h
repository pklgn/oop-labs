#pragma once
#include "pch.h"
#include "IStudent.h"

class IAdvancedStudent : public IStudent
{
public:
	virtual ~IAdvancedStudent();

	virtual std::string GetDissertationTheme() const = 0;

	virtual void SetDissertationTheme(std::string const& dissertationTheme) = 0;
};