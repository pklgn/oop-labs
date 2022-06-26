#pragma once
#include "pch.h"
#include "IAdvancedStudent.h"
#include "StudentImpl.hpp"

class AdvancedStudent : StudentImpl<IAdvancedStudent>
{
public:
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