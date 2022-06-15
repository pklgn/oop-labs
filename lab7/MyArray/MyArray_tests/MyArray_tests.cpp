#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MyArray.hpp"
#include <string>

TEST_CASE("Work with std::string")
{
	SECTION("Check initialized values")
	{
		MyArray<std::string, 0> stringArr;

		REQUIRE(stringArr.GetSize() == 0);
		REQUIRE_THROWS_AS(stringArr[0], std::out_of_range);
	}
	SECTION("Check default values")
	{
		std::string emptyString;
		MyArray<std::string, 2> stringArr;
		REQUIRE(stringArr.GetSize() == 2);
		REQUIRE(stringArr[0] == emptyString);
		REQUIRE(stringArr[1] == emptyString);
		REQUIRE_THROWS_AS(stringArr[2], std::out_of_range);
	}
	SECTION("Check PushBack method")
	{
		MyArray<std::string, 0> stringArr;

		REQUIRE(stringArr.GetSize() == 0);

		stringArr.PushBack("hello");
		REQUIRE(stringArr.GetSize() == 1);

		stringArr.PushBack("world");
		REQUIRE(stringArr.GetSize() == 2);

		stringArr.PushBack("");
		REQUIRE(stringArr.GetSize() == 3);
	}
	SECTION("Check Clear method")
	{
		MyArray<std::string, 0> stringArr;
		stringArr.PushBack("hello");
		stringArr.PushBack("world");
		stringArr.PushBack("");
		REQUIRE(stringArr.GetSize() == 3);

		REQUIRE_NOTHROW(stringArr.Clear());
		REQUIRE(stringArr.GetSize() == 0);
		REQUIRE_THROWS_AS(stringArr[0], std::out_of_range);
	}
	SECTION("Check Resize method and new size is bigger than current")
	{
		std::string emptyString;
		MyArray<std::string, 0> stringArr;
		stringArr.Resize(10);
		stringArr.PushBack("hello");
		stringArr.PushBack("world");
		stringArr.PushBack("");
		REQUIRE(stringArr.GetSize() == 13);

		REQUIRE(stringArr[0] == emptyString);
		REQUIRE(stringArr[1] == emptyString);
		REQUIRE(stringArr[2] == emptyString);

		REQUIRE(stringArr[10] == "hello");
		REQUIRE(stringArr[11] == "world");
		REQUIRE(stringArr[12] == emptyString);
	}

	SECTION("Check Resize method and new size is smaller than current")
	{
		std::string emptyString;
		MyArray<std::string, 0> stringArr;
		stringArr.PushBack("hello");
		stringArr.PushBack("world");
		stringArr.PushBack("");
		REQUIRE(stringArr.GetSize() == 3);

		REQUIRE_NOTHROW(stringArr.Resize(1));

		REQUIRE(stringArr[0] == "hello");
		REQUIRE_THROWS_AS(stringArr[1], std::out_of_range);
	}

	SECTION("Check Resize method and new size is bigger than current that not equals 0")
	{
		std::string emptyString;
		MyArray<std::string, 0> stringArr;
		stringArr.PushBack("hello");
		stringArr.PushBack("world");
		stringArr.PushBack("");
		REQUIRE(stringArr.GetSize() == 3);

		REQUIRE_NOTHROW(stringArr.Resize(10));

		REQUIRE(stringArr[0] == "hello");
		REQUIRE(stringArr[1] == "world");
		REQUIRE(stringArr[2] == "");

		REQUIRE(stringArr[7] == emptyString);
		REQUIRE(stringArr[8] == emptyString);
		REQUIRE(stringArr[9] == emptyString);
	}

	SECTION("Check assignment operator")
	{
		std::string line1 = "Survival of the richest";
		std::string line2 = "The city's ours until the fall";
		std::string line3 = "They're Monaco and Hamptons bound";
		std::string line4 = "But we don't feel like outsiders at all";

		MyArray<std::string, 0> couplet;
		couplet.PushBack(line1);
		couplet.PushBack(line2);
		couplet.PushBack(line3);
		couplet.PushBack(line4);

		MyArray<std::string, 0> copyCouplet;
		REQUIRE(copyCouplet.GetSize() == 0);

		copyCouplet = couplet;
		REQUIRE(copyCouplet.GetSize() == 4);

		std::string line5 = "";
		couplet.PushBack(line5);

		REQUIRE(copyCouplet.GetSize() == 4);
		REQUIRE(couplet.GetSize() == 5);

		couplet.PushBack(line5);

		REQUIRE(copyCouplet.GetSize() == 4);
		REQUIRE(couplet.GetSize() == 6);

		copyCouplet.PushBack(line1);
		REQUIRE(copyCouplet.GetSize() == 5);
		REQUIRE(couplet.GetSize() == 6);

		REQUIRE(copyCouplet[4] == line1);
		REQUIRE(couplet[5] == "");

		couplet = couplet;
		REQUIRE(couplet[5] == "");
		REQUIRE(couplet.GetSize() == 6);
	}

	SECTION("Check assignment constructor")
	{
		MyArray<std::string, 0> stringArr;
		stringArr.PushBack("hello");
		stringArr.PushBack("world");

		MyArray<std::string, 0> copyStringArr(stringArr);

		REQUIRE(copyStringArr.GetSize() == 2);
		REQUIRE(stringArr.GetSize() == 2);

		REQUIRE(copyStringArr[0] == "hello");
		REQUIRE(copyStringArr[1] == "world");

		REQUIRE(stringArr[0] == "hello");
		REQUIRE(stringArr[1] == "world");
	}

	SECTION("Check move contructor")
	{
		MyArray<std::string, 0> stringArr;
		stringArr.PushBack("hello");
		stringArr.PushBack("world");

		MyArray<std::string, 0> copyStringArr(std::move(stringArr));

		REQUIRE(stringArr.GetSize() == 0);

		REQUIRE(copyStringArr.GetSize() == 2);
		REQUIRE(copyStringArr[0] == "hello");
		REQUIRE(copyStringArr[1] == "world");

		copyStringArr.PushBack("");
		REQUIRE(stringArr.GetSize() == 0);
		REQUIRE(copyStringArr.GetSize() == 3);
	}

	SECTION("Check move operator")
	{
		MyArray<std::string, 0> stringArr;
		stringArr.PushBack("hello");
		stringArr.PushBack("world");

		MyArray<std::string, 0> movedStringArr;
		movedStringArr = std::move(stringArr);

		REQUIRE(stringArr.GetSize() == 0);

		REQUIRE(movedStringArr.GetSize() == 2);
		REQUIRE(movedStringArr[0] == "hello");
		REQUIRE(movedStringArr[1] == "world");

		movedStringArr.PushBack("");
		REQUIRE(stringArr.GetSize() == 0);
		REQUIRE(movedStringArr.GetSize() == 3);

		movedStringArr = std::move(movedStringArr);
		REQUIRE(movedStringArr.GetSize() == 3);
	}
}

TEST_CASE("Work with double")
{
	SECTION("Check initialized values")
	{
		MyArray<double, 0> stringArr;

		REQUIRE(stringArr.GetSize() == 0);
		REQUIRE_THROWS_AS(stringArr[0], std::out_of_range);
	}
	SECTION("Check default values")
	{
		double zero = 0;
		MyArray<double, 2> stringArr;
		REQUIRE(stringArr.GetSize() == 2);
		REQUIRE(stringArr[0] == zero);
		REQUIRE(stringArr[1] == zero);
		REQUIRE_THROWS_AS(stringArr[2], std::out_of_range);
	}
	SECTION("Check PushBack method")
	{
		MyArray<double, 0> stringArr;

		REQUIRE(stringArr.GetSize() == 0);

		stringArr.PushBack(3.4);
		REQUIRE(stringArr.GetSize() == 1);

		stringArr.PushBack(5.6);
		REQUIRE(stringArr.GetSize() == 2);

		stringArr.PushBack(7.8);
		REQUIRE(stringArr.GetSize() == 3);
	}
	SECTION("Check Clear method")
	{
		MyArray<double, 0> stringArr;
		stringArr.PushBack(1.2);
		stringArr.PushBack(3.4);
		stringArr.PushBack(5.6);
		REQUIRE(stringArr.GetSize() == 3);

		REQUIRE_NOTHROW(stringArr.Clear());
		REQUIRE(stringArr.GetSize() == 0);
		REQUIRE_THROWS_AS(stringArr[0], std::out_of_range);
	}
	SECTION("Check Resize method and new size is bigger than current")
	{
		double zero = 0;
		MyArray<double, 0> stringArr;
		stringArr.Resize(10);
		stringArr.PushBack(1.2);
		stringArr.PushBack(3.4);
		stringArr.PushBack(5.6);
		REQUIRE(stringArr.GetSize() == 13);

		REQUIRE(stringArr[0] == zero);
		REQUIRE(stringArr[1] == zero);
		REQUIRE(stringArr[2] == zero);

		REQUIRE(stringArr[10] == 1.2);
		REQUIRE(stringArr[11] == 3.4);
		REQUIRE(stringArr[12] == 5.6);
	}

	SECTION("Check Resize method and new size is smaller than current")
	{
		double zero = 0;
		MyArray<double, 0> stringArr;
		stringArr.PushBack(1.2);
		stringArr.PushBack(3.4);
		stringArr.PushBack(5.6);
		REQUIRE(stringArr.GetSize() == 3);

		REQUIRE_NOTHROW(stringArr.Resize(1));

		REQUIRE(stringArr[0] == 1.2);
		REQUIRE_THROWS_AS(stringArr[1], std::out_of_range);
	}

	SECTION("Check Resize method and new size is bigger than current that not equals 0")
	{
		double zero = 0;
		MyArray<double, 0> stringArr;
		stringArr.PushBack(1.2);
		stringArr.PushBack(3.4);
		stringArr.PushBack(5.6);
		REQUIRE(stringArr.GetSize() == 3);

		REQUIRE_NOTHROW(stringArr.Resize(10));

		REQUIRE(stringArr[0] == 1.2);
		REQUIRE(stringArr[1] == 3.4);
		REQUIRE(stringArr[2] == 5.6);

		REQUIRE(stringArr[7] == zero);
		REQUIRE(stringArr[8] == zero);
		REQUIRE(stringArr[9] == zero);
	}

	SECTION("Check assignment operator")
	{
		double line1 = 1.23;
		double line2 = 4.56;
		double line3 = 7.89;
		double line4 = 0.12;

		MyArray<double, 0> couplet;
		couplet.PushBack(line1);
		couplet.PushBack(line2);
		couplet.PushBack(line3);
		couplet.PushBack(line4);

		MyArray<double, 0> copyCouplet;
		REQUIRE(copyCouplet.GetSize() == 0);

		copyCouplet = couplet;
		REQUIRE(copyCouplet.GetSize() == 4);

		double line5 = 0;
		couplet.PushBack(line5);

		REQUIRE(copyCouplet.GetSize() == 4);
		REQUIRE(couplet.GetSize() == 5);

		couplet.PushBack(line5);

		REQUIRE(copyCouplet.GetSize() == 4);
		REQUIRE(couplet.GetSize() == 6);

		copyCouplet.PushBack(line1);
		REQUIRE(copyCouplet.GetSize() == 5);
		REQUIRE(couplet.GetSize() == 6);

		REQUIRE(copyCouplet[4] == line1);
		REQUIRE(couplet[5] == 0);

		couplet = couplet;
		REQUIRE(couplet[5] == 0);
		REQUIRE(couplet.GetSize() == 6);
	}

	SECTION("Check assignment constructor")
	{
		MyArray<double, 0> stringArr;
		stringArr.PushBack(1.2);
		stringArr.PushBack(3.4);

		MyArray<double, 0> copyStringArr(stringArr);

		REQUIRE(copyStringArr.GetSize() == 2);
		REQUIRE(stringArr.GetSize() == 2);

		REQUIRE(copyStringArr[0] == 1.2);
		REQUIRE(copyStringArr[1] == 3.4);

		REQUIRE(stringArr[0] == 1.2);
		REQUIRE(stringArr[1] == 3.4);
	}

	SECTION("Check move contructor")
	{
		MyArray<double, 0> stringArr;
		stringArr.PushBack(1.2);
		stringArr.PushBack(3.4);

		MyArray<double, 0> copyStringArr(std::move(stringArr));

		REQUIRE(stringArr.GetSize() == 0);

		REQUIRE(copyStringArr.GetSize() == 2);
		REQUIRE(copyStringArr[0] == 1.2);
		REQUIRE(copyStringArr[1] == 3.4);

		copyStringArr.PushBack(0);
		REQUIRE(stringArr.GetSize() == 0);
		REQUIRE(copyStringArr.GetSize() == 3);
	}

	SECTION("Check move operator")
	{
		MyArray<double, 0> stringArr;
		stringArr.PushBack(1.2);
		stringArr.PushBack(3.4);

		MyArray<double, 0> movedStringArr;
		movedStringArr = std::move(stringArr);

		REQUIRE(stringArr.GetSize() == 0);

		REQUIRE(movedStringArr.GetSize() == 2);
		REQUIRE(movedStringArr[0] == 1.2);
		REQUIRE(movedStringArr[1] == 3.4);

		movedStringArr.PushBack(0);
		REQUIRE(stringArr.GetSize() == 0);
		REQUIRE(movedStringArr.GetSize() == 3);

		movedStringArr = std::move(movedStringArr);
		REQUIRE(movedStringArr.GetSize() == 3);
	}
}