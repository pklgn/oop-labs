#pragma once
#include "pch.h"
#include "IWorker.h"
#include "PersonImpl.hpp"

class Worker : public PersonImpl<IWorker>
{
public:
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