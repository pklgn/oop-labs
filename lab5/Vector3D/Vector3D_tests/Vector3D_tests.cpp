#pragma once
#define CATCH_CONFIG_MAIN
#include "../Vector3D.h"
#include "../../../catch2/catch.hpp"

TEST_CASE("Create vector using constructor")
{
	SECTION("Default vector with length equals to 0")
	{
		Vector3D vector;
		REQUIRE(vector.x == 0);
		REQUIRE(vector.y == 0);
		REQUIRE(vector.z == 0);
	}

	SECTION("Parameterized contructor")
	{
		Vector3D vector(1.23, 4.56, 7.89);
		REQUIRE(vector.x == 1.23);
		REQUIRE(vector.y == 4.56);
		REQUIRE(vector.z == 7.89);
	}
}