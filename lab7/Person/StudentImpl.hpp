#pragma once
#include "pch.h"
#include "PersonImpl.hpp"

template <typename Base>
class StudentImpl : public PersonImpl<Base>
{
public:
	~StudentImpl() = default;

	virtual std::string GetUniversityName() const override
	{
		return m_universityName;
	}
	virtual std::string GetID() const override
	{
		return m_ID;
	}

	virtual void SetUniversityName(std::string const& universityName) override
	{
		m_universityName = universityName;
	}
	virtual void SetID(std::string const& ID) override
	{
		m_ID = ID;
	}

private:
	std::string m_universityName;
	std::string m_ID;
};