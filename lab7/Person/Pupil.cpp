#pragma once
#include "pch.h"
#include "IPupil.h"
#include "PersonImpl.hpp"

class Pupil : public PersonImpl<IPupil>
{
public:
	~Pupil() = default;

	virtual std::string GetSchoolName() const override
	{
		return m_schoolName;
	}
	virtual std::string GetClassName() const override
	{
		return m_className;
	}

	virtual void SetSchoolName(std::string const& schoolName) override
	{
		m_schoolName = schoolName;
	}
	virtual void SetClassName(std::string const& className) override
	{
		m_className = className;
	}

private:
	std::string m_schoolName;
	std::string m_className;
};