#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Pupil.hpp"
#include "../Teacher.hpp"
#include "../Student.hpp"
#include "../AdvancedStudent.hpp"
#include "../Worker.hpp"

TEST_CASE("Create pupil")
{
	THEN("He will have person attributes and plus school name and his class name")
	{
		Pupil pupil("Petr", "Petrov", "Petrovich", "Earth", "MIT", "1a");
		REQUIRE(pupil.GetName() == "Petr");
		REQUIRE(pupil.GetSurname() == "Petrov");
		REQUIRE(pupil.GetPatronymic() == "Petrovich");
		REQUIRE(pupil.GetAddress() == "Earth");
		REQUIRE(pupil.GetSchoolName() == "MIT");
		REQUIRE(pupil.GetSchoolClass() == "1a");
	}
}

TEST_CASE("Create teacher")
{
	THEN("He will have person attributes and plus school name and his class name")
	{
		Teacher teacher("Petr", "Petrov", "Petrovich", "Mars", "Biology");
		REQUIRE(teacher.GetName() == "Petr");
		REQUIRE(teacher.GetSurname() == "Petrov");
		REQUIRE(teacher.GetPatronymic() == "Petrovich");
		REQUIRE(teacher.GetAddress() == "Mars");
		REQUIRE(teacher.GetSubjectName() == "Biology");
	}
}

TEST_CASE("Create student")
{
	THEN("He will have person attributes and plus university name and his ID")
	{
		Student student("Petr", "Petrov", "Petrovich", "Mars", "Volgatech", "s123");
		REQUIRE(student.GetName() == "Petr");
		REQUIRE(student.GetSurname() == "Petrov");
		REQUIRE(student.GetPatronymic() == "Petrovich");
		REQUIRE(student.GetAddress() == "Mars");
		REQUIRE(student.GetUniversityName() == "Volgatech");
		REQUIRE(student.GetID() == "s123");
	}
}

TEST_CASE("Create advanced student")
{
	THEN("He will have person attributes and plus university name and his ID")
	{
		AdvancedStudent student("Petr", "Petrov", "Petrovich", "Mars", "Volgatech", "s123", "Artificial intelligence");
		REQUIRE(student.GetName() == "Petr");
		REQUIRE(student.GetSurname() == "Petrov");
		REQUIRE(student.GetPatronymic() == "Petrovich");
		REQUIRE(student.GetAddress() == "Mars");
		REQUIRE(student.GetUniversityName() == "Volgatech");
		REQUIRE(student.GetID() == "s123");
		REQUIRE(student.GetDissertationTheme() == "Artificial intelligence");
	}
}

TEST_CASE("Create worker")
{
	THEN("He will have person attributes and plusprofession")
	{
		Worker worker("Petr", "Petrov", "Petrovich", "Mars", "Cosmonaut");
		REQUIRE(worker.GetName() == "Petr");
		REQUIRE(worker.GetSurname() == "Petrov");
		REQUIRE(worker.GetPatronymic() == "Petrovich");
		REQUIRE(worker.GetAddress() == "Mars");
		REQUIRE(worker.GetProfession() == "Cosmonaut");
	}
}