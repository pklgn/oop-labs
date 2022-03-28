#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../vector_lib/vector_lib.h"

SCENARIO("Reading a stream which contains apropriate values of numbers")
{
	std::vector<double> numbers;
	std::ostringstream outputStream;
	WHEN("All values are integer")
	{
		std::istringstream inputStream("12 4 3");
		ReadNumbers(inputStream, numbers);
		std::vector<double> processedNumbers = MultiplyNegativeByMinMaxOfVector(numbers);
		PrintVector(processedNumbers, outputStream);
		THEN("Output stream will contain them with precision equals to 3 filled with 0")
		{
			REQUIRE(outputStream.str() == "3.000 4.000 12.000 \n");
		}
	}

	WHEN("Some values are double")
	{
		std::istringstream inputStream("12.9874 4.32 3");
		ReadNumbers(inputStream, numbers);
		std::vector<double> processedNumbers = MultiplyNegativeByMinMaxOfVector(numbers);
		PrintVector(processedNumbers, outputStream);
		THEN("Each number will be printed with precision equals to 3")
		{
			REQUIRE(outputStream.str() == "3.000 4.320 12.987 \n");
		}
	}

	WHEN("Amount of given values is not equals 0")
	{
		std::istringstream inputStream("12 4.32 3 123");
		ReadNumbers(inputStream, numbers);
		THEN("Every number will be read")
		{
			REQUIRE(numbers.size() == 4);
		}
	}

	WHEN("Some numbers are negative")
	{
		std::istringstream inputStream("12 4 3 -1");
		ReadNumbers(inputStream, numbers);
		std::vector<double> processedNumbers = MultiplyNegativeByMinMaxOfVector(numbers);
		PrintVector(processedNumbers, outputStream);
		THEN("Negative mumber will by multiplied by minmax")
		{
			REQUIRE(outputStream.str() == "3.000 4.000 12.000 12.000 \n");
		}
	}
}

SCENARIO("Reading a stream which contains inapropriate values of numbers")
{
	std::vector<double> numbers;
	std::ostringstream outputStream;

	WHEN("Invalid character was found")
	{
		std::istringstream inputStream("12 4 3q -1");
		ReadNumbers(inputStream, numbers);
		THEN("Vector of numbers will contain all collected numbers before")
		{
			REQUIRE(numbers.size() == 3);
		}
	}
}

SCENARIO("Reading an empty stream")
{
	std::vector<double> numbers;
	std::ostringstream outputStream;

	WHEN("Nothing is in stream")
	{
		std::istringstream inputStream;
		ReadNumbers(inputStream, numbers);
		THEN("Vector of numbers will be empty")
		{
			CHECK(numbers.empty());
		}
	}
}