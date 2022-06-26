#pragma once
#include "pch.h"
#include "IPerson.h"

template <class Base>
class PersonImpl : public Base
{
public:
	~PersonImpl() = default;

	virtual std::string GetName() const override
	{
		return m_name;
	}
	virtual std::string GetSurname() const override
	{
		return m_surname;
	}
	virtual std::string GetPatronymic() const override
	{
		return m_patronymic;
	}
	virtual std::string GetAddress() const override
	{
		return m_address;
	}

	virtual void SetName(std::string const& name) override
	{
		m_name = name;
	}	
	virtual void SetSurname(std::string const& surname) override
	{
		m_surname = surname;
	}	
	virtual void SetPatronymic(std::string const& patronymic) override
	{
		m_patronymic = patronymic;
	}	
	virtual void SetAddress(std::string const& address) override
	{
		m_address = address;
	}

private:
	std::string m_name;
	std::string m_surname;
	std::string m_patronymic;
	std::string m_address;
};