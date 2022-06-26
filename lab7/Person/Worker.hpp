#pragma once
#include "pch.h"
#include "IWorker.h"
#include "PersonImpl.hpp"

class Worker : public PersonImpl<IWorker>
{
public:
	Worker(std::string name, std::string surname, std::string patronymic, std::string address, std::string profession)
		: PersonImpl(name, surname, patronymic, address)
		, m_profession(profession)
	{
	}
	~Worker() = default;

	virtual std::string GetProfession() const override
	{
		return m_profession;
	}

	virtual void SetProfession(std::string const& profession) override
	{
		m_profession = profession;
	}

private:
	std::string m_profession;
};