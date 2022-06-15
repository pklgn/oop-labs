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
		MyArray<double, 0> doubleArr;

		REQUIRE(doubleArr.GetSize() == 0);
		REQUIRE_THROWS_AS(doubleArr[0], std::out_of_range);
	}
	SECTION("Check default values")
	{
		double zero = 0;
		MyArray<double, 2> doubleArr;
		REQUIRE(doubleArr.GetSize() == 2);
		REQUIRE(doubleArr[0] == zero);
		REQUIRE(doubleArr[1] == zero);
		REQUIRE_THROWS_AS(doubleArr[2], std::out_of_range);
	}
	SECTION("Check PushBack method")
	{
		MyArray<double, 0> doubleArr;

		REQUIRE(doubleArr.GetSize() == 0);

		doubleArr.PushBack(3.4);
		REQUIRE(doubleArr.GetSize() == 1);

		doubleArr.PushBack(5.6);
		REQUIRE(doubleArr.GetSize() == 2);

		doubleArr.PushBack(7.8);
		REQUIRE(doubleArr.GetSize() == 3);
	}
	SECTION("Check Clear method")
	{
		MyArray<double, 0> doubleArr;
		doubleArr.PushBack(1.2);
		doubleArr.PushBack(3.4);
		doubleArr.PushBack(5.6);
		REQUIRE(doubleArr.GetSize() == 3);

		REQUIRE_NOTHROW(doubleArr.Clear());
		REQUIRE(doubleArr.GetSize() == 0);
		REQUIRE_THROWS_AS(doubleArr[0], std::out_of_range);
	}
	SECTION("Check Resize method and new size is bigger than current")
	{
		double zero = 0;
		MyArray<double, 0> doubleArr;
		doubleArr.Resize(10);
		doubleArr.PushBack(1.2);
		doubleArr.PushBack(3.4);
		doubleArr.PushBack(5.6);
		REQUIRE(doubleArr.GetSize() == 13);

		REQUIRE(doubleArr[0] == zero);
		REQUIRE(doubleArr[1] == zero);
		REQUIRE(doubleArr[2] == zero);

		REQUIRE(doubleArr[10] == 1.2);
		REQUIRE(doubleArr[11] == 3.4);
		REQUIRE(doubleArr[12] == 5.6);
	}

	SECTION("Check Resize method and new size is smaller than current")
	{
		double zero = 0;
		MyArray<double, 0> doubleArr;
		doubleArr.PushBack(1.2);
		doubleArr.PushBack(3.4);
		doubleArr.PushBack(5.6);
		REQUIRE(doubleArr.GetSize() == 3);

		REQUIRE_NOTHROW(doubleArr.Resize(1));

		REQUIRE(doubleArr[0] == 1.2);
		REQUIRE_THROWS_AS(doubleArr[1], std::out_of_range);
	}

	SECTION("Check Resize method and new size is bigger than current that not equals 0")
	{
		double zero = 0;
		MyArray<double, 0> doubleArr;
		doubleArr.PushBack(1.2);
		doubleArr.PushBack(3.4);
		doubleArr.PushBack(5.6);
		REQUIRE(doubleArr.GetSize() == 3);

		REQUIRE_NOTHROW(doubleArr.Resize(10));

		REQUIRE(doubleArr[0] == 1.2);
		REQUIRE(doubleArr[1] == 3.4);
		REQUIRE(doubleArr[2] == 5.6);

		REQUIRE(doubleArr[7] == zero);
		REQUIRE(doubleArr[8] == zero);
		REQUIRE(doubleArr[9] == zero);
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
		MyArray<double, 0> doubleArr;
		doubleArr.PushBack(1.2);
		doubleArr.PushBack(3.4);

		MyArray<double, 0> copyDoubleArr(doubleArr);

		REQUIRE(copyDoubleArr.GetSize() == 2);
		REQUIRE(doubleArr.GetSize() == 2);

		REQUIRE(copyDoubleArr[0] == 1.2);
		REQUIRE(copyDoubleArr[1] == 3.4);

		REQUIRE(doubleArr[0] == 1.2);
		REQUIRE(doubleArr[1] == 3.4);
	}

	SECTION("Check move contructor")
	{
		MyArray<double, 0> doubleArr;
		doubleArr.PushBack(1.2);
		doubleArr.PushBack(3.4);

		MyArray<double, 0> copyDoubleArr(std::move(doubleArr));

		REQUIRE(doubleArr.GetSize() == 0);

		REQUIRE(copyDoubleArr.GetSize() == 2);
		REQUIRE(copyDoubleArr[0] == 1.2);
		REQUIRE(copyDoubleArr[1] == 3.4);

		copyDoubleArr.PushBack(0);
		REQUIRE(doubleArr.GetSize() == 0);
		REQUIRE(copyDoubleArr.GetSize() == 3);
	}

	SECTION("Check move operator")
	{
		MyArray<double, 0> doubleArr;
		doubleArr.PushBack(1.2);
		doubleArr.PushBack(3.4);

		MyArray<double, 0> movedDoubleArr;
		movedDoubleArr = std::move(doubleArr);

		REQUIRE(doubleArr.GetSize() == 0);

		REQUIRE(movedDoubleArr.GetSize() == 2);
		REQUIRE(movedDoubleArr[0] == 1.2);
		REQUIRE(movedDoubleArr[1] == 3.4);

		movedDoubleArr.PushBack(0);
		REQUIRE(doubleArr.GetSize() == 0);
		REQUIRE(movedDoubleArr.GetSize() == 3);

		movedDoubleArr = std::move(movedDoubleArr);
		REQUIRE(movedDoubleArr.GetSize() == 3);
	}
}

TEST_CASE("Check iterator const version")
{
	MyArray<std::string, 0> stringArr;
	stringArr.PushBack("hello");
	stringArr.PushBack("world");
	const MyArray<std::string, 0> exampleArr(stringArr);

	SECTION("Check begin and end const iterator methods")
	{
		MyArray<std::string, 0>::const_iterator beginIt = exampleArr.begin();
		REQUIRE(*beginIt == "hello");

		MyArray<std::string, 0>::const_iterator endIt = exampleArr.end();
		REQUIRE(*(endIt - 1) == "world");
	}
}

TEST_CASE("Check iterator operators")
{
	std::string line1 = "Survival of the richest";
	std::string line2 = "The city's ours until the fall";
	std::string line3 = "They're Monaco and Hamptons bound";
	std::string line4 = "But we don't feel like outsiders at all";

	MyArray<std::string, 0> exampleArr;
	exampleArr.PushBack(line1);
	exampleArr.PushBack(line2);
	exampleArr.PushBack(line3);
	exampleArr.PushBack(line4);

	SECTION("Check operator*")
	{
		MyArray<std::string, 0>::const_iterator beginIt = exampleArr.begin();
		REQUIRE(*beginIt == line1);

		MyArray<std::string, 0>::const_iterator endIt = exampleArr.end();
		REQUIRE(*(endIt - 1) == line4);
	}

	SECTION("Check operator++")
	{
		MyArray<std::string, 0>::const_iterator it = exampleArr.begin();
		for (size_t i = 0; i < 2; ++i, ++it)
		{
			REQUIRE(exampleArr[i] == *it);
		}

		REQUIRE(*it == line3);
	}

	SECTION("Check operator--")
	{
		MyArray<std::string, 0>::const_iterator it = exampleArr.end();
		REQUIRE(*(it - 1) == line4);
		--it;

		REQUIRE(*it == line4);
	}

	SECTION("Check operator+=")
	{
		MyArray<std::string, 0>::const_iterator it = exampleArr.begin();

		REQUIRE(*it == line1);

		it += 1;
		REQUIRE(*it == line2);

		it += 2;
		REQUIRE(*it == line4);
	}

	SECTION("Check operator-=")
	{
		MyArray<std::string, 0>::const_iterator it = exampleArr.end();

		it -= 1;
		REQUIRE(*it == line4);

		it -= 2;
		REQUIRE(*it == line2);
	}

	SECTION("Check operator-")
	{
		MyArray<std::string, 0>::const_iterator beginIt = exampleArr.begin();
		MyArray<std::string, 0>::const_iterator endIt = exampleArr.end();

		REQUIRE(endIt - beginIt == exampleArr.GetSize());

		--endIt;
		REQUIRE(endIt - beginIt == exampleArr.GetSize() - 1);

		++beginIt;
		REQUIRE(endIt - beginIt == exampleArr.GetSize() - 2);
	}

	SECTION("Check operator<")
	{
		MyArray<std::string, 0>::const_iterator beginIt = exampleArr.begin();
		MyArray<std::string, 0>::const_iterator endIt = exampleArr.end();

		REQUIRE(beginIt < endIt);
		REQUIRE(!(endIt < beginIt));

		beginIt += exampleArr.GetSize();
		REQUIRE(!(beginIt < endIt));
	}

	SECTION("Check operator>")
	{
		MyArray<std::string, 0>::const_iterator beginIt = exampleArr.begin();
		MyArray<std::string, 0>::const_iterator endIt = exampleArr.end();

		REQUIRE(endIt > beginIt);
		REQUIRE(!(beginIt > endIt));

		beginIt += exampleArr.GetSize();
		REQUIRE(!(beginIt > endIt));
	}

	SECTION("Check operator<=")
	{
		MyArray<std::string, 0>::const_iterator beginIt = exampleArr.begin();
		MyArray<std::string, 0>::const_iterator endIt = exampleArr.end();

		REQUIRE(beginIt <= endIt);

		beginIt += exampleArr.GetSize();
		REQUIRE(beginIt <= endIt);
	}

	SECTION("Check operator>=")
	{
		MyArray<std::string, 0>::const_iterator beginIt = exampleArr.begin();
		MyArray<std::string, 0>::const_iterator endIt = exampleArr.end();

		REQUIRE(endIt >= beginIt);

		beginIt += exampleArr.GetSize();
		REQUIRE(beginIt >= endIt);
	}

	SECTION("Check operator[]")
	{
		MyArray<std::string, 0>::const_iterator beginIt = exampleArr.begin();
		MyArray<std::string, 0>::const_iterator endIt = exampleArr.end();

		REQUIRE(beginIt[0] == line1);
		REQUIRE(beginIt[1] == line2);
		REQUIRE(beginIt[2] == line3);
		REQUIRE(beginIt[3] == line4);

		REQUIRE(endIt[-1] == line4);
		REQUIRE(endIt[-2] == line3);
	}
}

TEST_CASE("Check not const iterator")
{
	MyArray<std::string, 0> exampleArr;
	exampleArr.PushBack("hello");
	exampleArr.PushBack("world");

	SECTION("Check begin and end not const iterator methods")
	{
		MyArray<std::string, 0>::const_iterator beginIt = exampleArr.begin();
		REQUIRE(*beginIt == "hello");

		MyArray<std::string, 0>::const_iterator endIt = exampleArr.end();
		REQUIRE(*(endIt - 1) == "world");
	}
}

TEST_CASE("Check operators for not const iterator")
{
	std::string line1 = "Survival of the richest";
	std::string line2 = "The city's ours until the fall";
	std::string line3 = "They're Monaco and Hamptons bound";
	std::string line4 = "But we don't feel like outsiders at all";
	
	MyArray<std::string, 0> exampleArr;
	exampleArr.PushBack(line1);
	exampleArr.PushBack(line2);
	exampleArr.PushBack(line3);
	exampleArr.PushBack(line4);


	SECTION("Check operator= from begin")
	{
		MyArray<std::string, 0>::iterator it = exampleArr.begin();

		REQUIRE(*it == line1);

		*it = "test";
		REQUIRE(exampleArr[0] == "test");

		it += 1;
		REQUIRE(*it == line2);

		*it = "test2";
		REQUIRE(exampleArr[1] == "test2");
	}

	SECTION("Check operator= from end")
	{
		MyArray<std::string, 0>::iterator it = exampleArr.end();

		REQUIRE(*(it - 1) == line4);

		*it--;
		*it = "line4";

		*it--;
		*it = "line3";

		REQUIRE(exampleArr[3] == "line4");
		REQUIRE(exampleArr[2] == "line3");

		MyArray<std::string, 0>::iterator it2 = exampleArr.end();
		it2 -= 3;
		*it2 = "line2";
		REQUIRE(exampleArr[1] == "line2");
	}

	SECTION("Check operator<")
	{
		MyArray<std::string, 0>::iterator beginIt = exampleArr.begin();
		MyArray<std::string, 0>::iterator endIt = exampleArr.end();

		REQUIRE(beginIt < endIt);
		REQUIRE(!(endIt < beginIt));

		beginIt += exampleArr.GetSize();
		REQUIRE(!(beginIt < endIt));
	}

	SECTION("Check operator>")
	{
		MyArray<std::string, 0>::iterator beginIt = exampleArr.begin();
		MyArray<std::string, 0>::iterator endIt = exampleArr.end();

		REQUIRE(endIt > beginIt);
		REQUIRE(!(beginIt > endIt));

		beginIt += exampleArr.GetSize();
		REQUIRE(!(beginIt > endIt));
	}

	SECTION("Check operator<=")
	{
		MyArray<std::string, 0>::iterator beginIt = exampleArr.begin();
		MyArray<std::string, 0>::iterator endIt = exampleArr.end();

		REQUIRE(beginIt <= endIt);

		beginIt += exampleArr.GetSize();
		REQUIRE(beginIt <= endIt);
	}

	SECTION("Check operator>=")
	{
		MyArray<std::string, 0>::iterator beginIt = exampleArr.begin();
		MyArray<std::string, 0>::iterator endIt = exampleArr.end();

		REQUIRE(endIt >= beginIt);

		beginIt += exampleArr.GetSize();
		REQUIRE(beginIt >= endIt);
	}
}

TEST_CASE("Check reverse iterator")
{
	std::string line1 = "Survival of the richest";
	std::string line2 = "The city's ours until the fall";
	std::string line3 = "They're Monaco and Hamptons bound";
	std::string line4 = "But we don't feel like outsiders at all";

	MyArray<std::string, 0> exampleArr;
	exampleArr.PushBack(line1);
	exampleArr.PushBack(line2);
	exampleArr.PushBack(line3);
	exampleArr.PushBack(line4);

	SECTION("Check const reverse iterator")
	{
		MyArray<std::string, 0>::const_reverse_iterator rIt = exampleArr.rend() - 1;
		for (size_t i = 0; i < exampleArr.GetSize(); ++i, --rIt)
		{
			REQUIRE(exampleArr[i] == *rIt);
		}

		MyArray<std::string, 0>::const_reverse_iterator rBeginIt = exampleArr.rbegin();
		REQUIRE(*rBeginIt == line4);

		++rBeginIt;
		REQUIRE(*rBeginIt == line3);

		++rBeginIt;
		REQUIRE(*rBeginIt == line2);

		++rBeginIt;
		REQUIRE(*rBeginIt == line1);

		MyArray<std::string, 0>::const_reverse_iterator rEndIt = exampleArr.rend() - 1;
		REQUIRE(*rEndIt == line1);

		--rEndIt;
		REQUIRE(*rEndIt == line2);

		-- --rEndIt;
		REQUIRE(*rEndIt == line4);
	}
}