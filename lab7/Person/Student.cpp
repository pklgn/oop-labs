#pragma once
#include "pch.h"
#include "IStudent.h"
#include "StudentImpl.hpp"

class Student : StudentImpl<IStudent>
{
public:
	~Student() = default;

	virtual std::string GetUniversityName() const override
	{
		return m_universityName;
	}
	virtual std::string GetID() const override
	{
		return m_ID;
	}

	virtual void SetUniversityName(std::string const& univesityName) override
	{
		m_universityName = univesityName;
	}
	virtual void SetID(std::string const& ID) override
	{
		m_ID = ID;
	}

private:
	std::string m_universityName;
	std::string m_ID;
};