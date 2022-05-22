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

TEST_CASE("Unary operations")
{
	Vector3D defaultVector;
	Vector3D vector(1.41, 2.89, 3.24);
	Vector3D newVector;
	SECTION("Unary +")
	{
		newVector = +vector;
		REQUIRE(newVector.x == 1.41); 
		REQUIRE(newVector.y == 2.89); 
		REQUIRE(newVector.z == 3.24); 

		newVector = +defaultVector;
		REQUIRE(newVector.x == 0);
		REQUIRE(newVector.y == 0);
		REQUIRE(newVector.z == 0); 
	}

	SECTION("Unary -")
	{
		newVector = -vector;
		REQUIRE(newVector.x == -1.41);
		REQUIRE(newVector.y == -2.89);
		REQUIRE(newVector.z == -3.24);

		newVector = -defaultVector;
		REQUIRE(newVector.x == 0);
		REQUIRE(newVector.y == 0);
		REQUIRE(newVector.z == 0); 
	}
}

TEST_CASE("Binary operations")
{
	Vector3D vector;
}