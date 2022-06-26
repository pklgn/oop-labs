#pragma once
#include "pch.h"
#include "IPupil.h"
#include "PersonImpl.hpp"

class Pupil : public PersonImpl<IPupil>
{
public:
	Pupil(std::string name, std::string surname, std::string patronymic, std::string address, std::string schoolName, std::string schoolClass)
		: PersonImpl(name, surname, patronymic, address)
		, m_schoolName(schoolName)
		, m_schoolClass(schoolClass)
	{
	}
	~Pupil() = default;

	virtual std::string GetSchoolName() const override
	{
		return m_schoolName;
	}
	virtual std::string GetSchoolClass() const override
	{
		return m_schoolClass;
	}

	virtual void SetSchoolName(std::string const& schoolName) override
	{
		m_schoolName = schoolName;
	}
	virtual void SetSchoolClass(std::string const& schoolClass) override
	{
		m_schoolClass = schoolClass;
	}

private:
	std::string m_schoolName;
	std::string m_schoolClass;
};