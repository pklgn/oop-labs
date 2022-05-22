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
	Vector3D firstVector(1.23, 4.24, 7.25);
	Vector3D secondVector(1.231, 4.242, 7.253);
	Vector3D firstDefaultVector;
	Vector3D secondDefaultVector;
	Vector3D resultVector;

	SECTION("Binary +")
	{
		resultVector = firstDefaultVector + secondDefaultVector;
		REQUIRE(resultVector.x == 0);
		REQUIRE(resultVector.y == 0);
		REQUIRE(resultVector.z == 0); 

		resultVector = firstVector + secondVector;

		REQUIRE(Approx(resultVector.x).margin(0.0001) == 2.461);
		REQUIRE(Approx(resultVector.y).margin(0.0001) == 8.482);
		REQUIRE(Approx(resultVector.z).margin(0.0001) == 14.503);
	}

	SECTION("Binary -")
	{
		resultVector = firstDefaultVector - secondDefaultVector;
		REQUIRE(resultVector.x == 0);
		REQUIRE(resultVector.y == 0);
		REQUIRE(resultVector.z == 0);

		resultVector = firstVector - secondVector;

		REQUIRE(Approx(resultVector.x).margin(0.0001) == -0.001);
		REQUIRE(Approx(resultVector.y).margin(0.0001) == -0.002);
		REQUIRE(Approx(resultVector.z).margin(0.0001) == -0.003);
	}
}

TEST_CASE("Operations combined with assignment")
{
	Vector3D firstVector(-1.32, -4.24, -7.35);
	Vector3D secondVector(-1.321, 4.242, 7.253);
	Vector3D firstDefaultVector;
	Vector3D secondDefaultVector;

	SECTION("Addition")
	{
		firstVector += secondVector;
		REQUIRE(Approx(firstVector.x).margin(0.0001) == -2.641);
		REQUIRE(Approx(firstVector.y).margin(0.0001) == 0.002);
		REQUIRE(Approx(firstVector.z).margin(0.0001) == -0.097);

		firstDefaultVector += secondDefaultVector;
		REQUIRE(firstDefaultVector.x == 0);
		REQUIRE(firstDefaultVector.y == 0);
		REQUIRE(firstDefaultVector.z == 0);
	}

	SECTION("Subtraction")
	{
		firstVector -= secondVector;
		REQUIRE(Approx(firstVector.x).margin(0.0001) == 0.001);
		REQUIRE(Approx(firstVector.y).margin(0.0001) == -8.482);
		REQUIRE(Approx(firstVector.z).margin(0.0001) == -14.603);

		firstDefaultVector -= secondDefaultVector;
		REQUIRE(firstDefaultVector.x == 0);
		REQUIRE(firstDefaultVector.y == 0);
		REQUIRE(firstDefaultVector.z == 0);
	}

	Vector3D thirdVector(2, 4, 5);
	SECTION("Multiplication")
	{
		thirdVector *= 4;
		REQUIRE(Approx(thirdVector.x).margin(0.0001) == 8);
		REQUIRE(Approx(thirdVector.y).margin(0.0001) == 16);
		REQUIRE(Approx(thirdVector.z).margin(0.0001) == 20);

		firstDefaultVector *= 5;
		REQUIRE(firstDefaultVector.x == 0);
		REQUIRE(firstDefaultVector.y == 0);
		REQUIRE(firstDefaultVector.z == 0);
	}

	SECTION("Division")
	{
		thirdVector /= 2;
		REQUIRE(Approx(thirdVector.x).margin(0.0001) == 1);
		REQUIRE(Approx(thirdVector.y).margin(0.0001) == 2);
		REQUIRE(Approx(thirdVector.z).margin(0.0001) == 2.5);

		firstDefaultVector /= 5;
		REQUIRE(firstDefaultVector.x == 0);
		REQUIRE(firstDefaultVector.y == 0);
		REQUIRE(firstDefaultVector.z == 0);

		secondVector /= 0;
		REQUIRE(Approx(secondVector.x).margin(0.0001) == -INFINITY);
		REQUIRE(Approx(secondVector.y).margin(0.0001) == INFINITY);
		REQUIRE(Approx(secondVector.z).margin(0.0001) == INFINITY);
	}
}

TEST_CASE("Checks vectors for approximate equality ")
{
	Vector3D firstVector(-1.32, -4.24, -7.35);
	Vector3D secondVector(-1.321, 4.242, 7.253);
	Vector3D thirdVector(-1.32, -4.24, -7.35);

	SECTION("Check two equal vectors")
	{
		REQUIRE(firstVector == thirdVector);
	}

	SECTION("Check two different vectors")
	{
		REQUIRE(firstVector != secondVector);
	}

	SECTION("Check two vectors with difference equal to DBL_EPSILON")
	{
		Vector3D epsilonVector(DBL_EPSILON, DBL_EPSILON, DBL_EPSILON);
		Vector3D forthVector = firstVector + epsilonVector;
		REQUIRE(firstVector == forthVector);
	}

	SECTION("Check two vectors with difference equal to DBL_EPSILON * 2 and DBL_EPSILON")
	{
		Vector3D epsilonVector(DBL_EPSILON * 2, DBL_EPSILON, DBL_EPSILON);
		Vector3D forthVector = firstVector + epsilonVector;
		REQUIRE(firstVector != forthVector);
	}
}

TEST_CASE("Binary multiplication and division operations")
{
	Vector3D vector(-1.32, -4.24, -7.35);
	Vector3D resultVector;

	SECTION("Multiplication")
	{
		resultVector = vector * 2;

	}
}