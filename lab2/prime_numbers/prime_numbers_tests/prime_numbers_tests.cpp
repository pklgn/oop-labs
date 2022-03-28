#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../prime_numbers_lib/prime_number_lib.h"

SCENARIO("Giving to the function valid values")
{
	WHEN("Input value is negative")
	{
		const std::set<int> result = GeneratePrimeNumbersSet(-2);
		THEN("The result set will be empty")
		{
			REQUIRE(result.empty());
		}
	}

	WHEN("Input value is less than the minimum prime number which equals 2")
	{
		const std::set<int> result = GeneratePrimeNumbersSet(1);
		THEN("The result set will be empty")
		{
			REQUIRE(result.empty());
		}
	}

	WHEN("Input value is small enough to calculate it by myself")
	{
		const std::set<int> set = GeneratePrimeNumbersSet(100);
		THEN("Size of the result for upperBound = 100 will be equal to 25")
		{
			REQUIRE(set.size() == 25);
		}
	}

	WHEN("Input value is the maximum")
	{
		const std::set<int> set = GeneratePrimeNumbersSet(100000000);
		THEN("Size of the result for upperBound = 100000000 will be equal to 5761455")
		{
			REQUIRE(set.size() == 5761455);
		}
	}
}
// TODO: сделать нагрузочный тест только для release версии
// TODO: добавить тест для границы, которой является простое число, напр 101