#pragma once
#include "pch.h"
#include "ITeacher.h"
#include "PersonImpl.hpp"

class Teacher : public PersonImpl<ITeacher>
{
public:
	Teacher(std::string name, std::string surname, std::string patronymic, std::string address, std::string subjectName)
		: PersonImpl(name, surname, patronymic, address)
		, m_subjectName(subjectName)
	{
	}
	~Teacher() = default;

	virtual std::string GetSubjectName() const override
	{
		return m_subjectName;
	}

	virtual void SetSubjectName(std::string const& subjectName) override
	{
		m_subjectName = subjectName;
	}

private:
	std::string m_subjectName;
};