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
	Vector3D defaultVector;
	Vector3D resultVector;

	SECTION("Multiplication")
	{
		resultVector = vector * 2;
		Vector3D doubledVector(-2.64, -8.48, -14.7);
		REQUIRE(resultVector == doubledVector);

		resultVector = 2 * vector;
		REQUIRE(resultVector == doubledVector);


		resultVector = defaultVector * 3;
		REQUIRE(resultVector == defaultVector);
	}

	SECTION("Division")
	{
		resultVector = vector / 2;
		Vector3D halfVector(-0.66, -2.12, -3.675);
		REQUIRE(resultVector == halfVector);

		resultVector = vector / 0;
		REQUIRE(!resultVector.IsValid());
	}
}

TEST_CASE("Check work with streams")
{
	std::istringstream inputStream("4.1, 5, 6\n4, 5, a");
	Vector3D initialVector(4.1, 5, 6);
	std::ostringstream outputStream;
	Vector3D vector;
	SECTION("Check input operation")
	{
		inputStream >> vector;
		REQUIRE(vector == initialVector);

		inputStream >> vector;
		REQUIRE(inputStream.fail());
	}

	SECTION("Check output")
	{
		outputStream << initialVector << std::endl << initialVector * 2;
		REQUIRE(outputStream.str() == "4.1, 5, 6\n8.2, 10, 12");
	}
}

TEST_CASE("Check vector functions")
{
	SECTION("Check scalar mul")
	{
		Vector3D vector1(1.2, 3.2, 3.21);
		Vector3D vector2(1, 3, 3);

		REQUIRE(DotProduct(vector1, vector2) == 20.43);
	}

	SECTION("Check vector mul")
	{
		Vector3D vector1(1, 2, 3);
		Vector3D vector2(4, 5, 6);
		Vector3D resultVectorMul(-3, 6, -3);

		REQUIRE(CrossProduct(vector1, vector2) == resultVectorMul);
	}

	SECTION("Check vector normalization")
	{
		Vector3D vector(5, -2, 7);
		double vectorLength = std::sqrt(78);
		Vector3D resultVector(5 / vectorLength, -2 / vectorLength, 7 / vectorLength);

		REQUIRE(Normalize(vector) == resultVector);

		Vector3D defaultVector;
		REQUIRE(!Normalize(defaultVector).IsValid());
	}

	SECTION("Check vector length")
	{
		Vector3D vector(4, 5, 6);
		REQUIRE(vector.GetLength() == std::sqrt(77));

		Vector3D defaultVector;
		REQUIRE(defaultVector.GetLength() == 0);

		Vector3D fractionalVector(1.2, -3.4, -7);
		REQUIRE(Approx(fractionalVector.GetLength()).margin(0.0001) == std::sqrt(62));
	}
}