#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../FindMaxEx.hpp"
#include "Sportsman/Sportsman.h"

template <typename T>
bool LessThan(T const& first, T const& second)
{
	return first < second;
}

bool StringLessThan(const char* first, const char* second)
{
	return strcmp(first, second) < 0;
}

TEST_CASE("Compare vector of simple data")
{
	SECTION("Empty vector of integers")
	{
		std::vector<int> intVector;

		int result = -1;
		bool wasFound = FindMaxEx(intVector, result, LessThan<int>);

		REQUIRE_FALSE(wasFound);
		REQUIRE(result == -1);
		REQUIRE(intVector.size() == 0);
	}

	SECTION("Not empty vector of integers")
	{
		std::vector<int> intVector;
		for (int i = 1; i < 10; ++i)
		{
			intVector.push_back(i);
		}
		int result;
		bool wasFound = FindMaxEx(intVector, result, LessThan<int>);

		REQUIRE(wasFound);
		REQUIRE(result == 9);
	}

	SECTION("Vector of doubles")
	{
		std::vector<double> doubleVector;
		for (double i = 1.3; i > -10; --i)
		{
			doubleVector.push_back(i);
		}
		double result;
		bool wasFound = FindMaxEx(doubleVector, result, LessThan<double>);

		REQUIRE(wasFound);
		REQUIRE(result == 1.3);
	}

	SECTION("Vector of strings")
	{
		std::vector<const char*> stringVector = { "string", "stig", "the stig", "stig's american cousin" };

		const char* result;
		bool wasFound = FindMaxEx(stringVector, result, StringLessThan);

		REQUIRE(wasFound);
		REQUIRE(result == "the stig");
	}
}

TEST_CASE("Compare vector of complex data")
{
	std::vector<Sportsman> atpRankings = {
		Sportsman{ "Daniil Medvedev", 198, 83 },
		Sportsman{ "Alexander Zverev", 198, 90 },
		Sportsman{ "Novak Djokovic", 188, 77 },
		Sportsman{ "Rafael Nadal", 185, 85 },
		Sportsman{ "Casper Ruud", 183, 77 }
	};

	SECTION("Work with sportsmen height")
	{
		Sportsman result;
		bool wasFound = FindMaxEx(atpRankings, result, HeightLessThan);
		
		REQUIRE(wasFound);
		REQUIRE(result.height == 198);
		REQUIRE(result.name == "Daniil Medvedev");
	}

	SECTION("Work with sportsmen weight")
	{
		Sportsman result;
		bool wasFound = FindMaxEx(atpRankings, result, WeightLessThan);

		REQUIRE(wasFound);
		REQUIRE(result.weight == 90);
		REQUIRE(result.name == "Alexander Zverev");
	}

	SECTION("Work with empty sportsmen vector with height compare")
	{
		std::vector<Sportsman> emptyRankings;
		Sportsman result = atpRankings[0];
		bool wasFound = FindMaxEx(emptyRankings, result, HeightLessThan);

		REQUIRE_FALSE(wasFound);
		REQUIRE(result.height == 198);
		REQUIRE(result.name == "Daniil Medvedev");
		REQUIRE(result.weight == 83);
	}

	SECTION("Work with empty sportsmen vector with weight compare")
	{
		std::vector<Sportsman> emptyRankings;
		Sportsman result = atpRankings[0];
		bool wasFound = FindMaxEx(emptyRankings, result, WeightLessThan);

		REQUIRE_FALSE(wasFound);
		REQUIRE(result.height == 198);
		REQUIRE(result.name == "Daniil Medvedev");
		REQUIRE(result.weight == 83);
	}

	std::vector<Sportsman> singleRankings = { atpRankings[0] };

	SECTION("Work with single sportsmen in the vector with weight compare")
	{
		Sportsman result = atpRankings[0];
		bool wasFound = FindMaxEx(singleRankings, result, WeightLessThan);

		REQUIRE(wasFound);
		REQUIRE(result.height == 198);
		REQUIRE(result.name == "Daniil Medvedev");
		REQUIRE(result.weight == 83);
	}
	
	SECTION("Work with single sportsmen in the vector with height compare")
	{
		Sportsman result = atpRankings[0];
		bool wasFound = FindMaxEx(singleRankings, result, HeightLessThan);

		REQUIRE(wasFound);
		REQUIRE(result.height == 198);
		REQUIRE(result.name == "Daniil Medvedev");
		REQUIRE(result.weight == 83);
	}
}