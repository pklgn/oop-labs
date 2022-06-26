#pragma once
#include "pch.h"
#include "IStudent.h"
#include "StudentImpl.hpp"

class Student : public StudentImpl<IStudent>
{
public:
	Student(std::string name, std::string surname, std::string patronymic, std::string address, std::string universityName, std::string ID)
		: StudentImpl(name, surname, patronymic, address, universityName, ID)
	{
	}
	~Student() = default;
};