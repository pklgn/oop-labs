#pragma once
#include "pch.h"
#include "PersonImpl.hpp"

template <typename Base>
class StudentImpl : public PersonImpl<Base>
{
public:
	StudentImpl(std::string name, std::string surname, std::string patronymic, std::string address, std::string universityName, std::string ID)
		: PersonImpl<Base>(name, surname, patronymic, address)
		, m_universityName(universityName)
		, m_ID(ID)
	{
	}

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