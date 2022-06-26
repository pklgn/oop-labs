#pragma once
#include "pch.h"
#include "IAdvancedStudent.h"
#include "StudentImpl.hpp"

class AdvancedStudent : public StudentImpl<IAdvancedStudent>
{
public:
	AdvancedStudent(std::string name, std::string surname, std::string patronymic, std::string address, std::string universityName, std::string ID, std::string dissertationTheme)
		: StudentImpl(name, surname, patronymic, address, universityName, ID)
		, m_dissertationTheme(dissertationTheme)
	{
	}
	~AdvancedStudent() = default;

	virtual std::string GetDissertationTheme() const override
	{
		return m_dissertationTheme;
	}

	virtual void SetDissertationTheme(std::string const& dissertationTheme) override
	{
		m_dissertationTheme = dissertationTheme;
	}

private:
	std::string m_dissertationTheme;
};