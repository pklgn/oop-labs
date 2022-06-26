#pragma once
#include "pch.h"
#include "IPerson.h"

class IWorker : public IPerson
{
public:
	virtual ~IWorker();

	virtual std::string GetProfession() const = 0;

	virtual void SetProfession(std::string const& profession) = 0;
};