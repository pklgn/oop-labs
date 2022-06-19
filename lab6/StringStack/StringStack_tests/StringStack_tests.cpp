#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../StringStack.h"

TEST_CASE("Check class contructor")
{
	SECTION("Constructor without params")
	{
		StringStack stringStack;

		REQUIRE(stringStack.GetSize() == 0);
		REQUIRE(stringStack.IsEmpty());
		REQUIRE_THROWS_AS(stringStack.GetTop(), std::logic_error);
	}
}

TEST_CASE("Check stack methods")
{
	StringStack stringStack = StringStack();

	SECTION("Check push method")
	{
		stringStack.Push("test");

		REQUIRE(stringStack.GetSize() == 1);
		REQUIRE(!stringStack.IsEmpty());
		REQUIRE(stringStack.GetTop() == "test");
	}

	SECTION("Check multiple push methods")
	{
		stringStack.Push("test1");
		stringStack.Push("test2");
		stringStack.Push("test3");

		REQUIRE(stringStack.GetSize() == 3);
		REQUIRE(!stringStack.IsEmpty());
		REQUIRE(stringStack.GetTop() == "test3");
	}

	SECTION("Check pop method")
	{
		stringStack.Push("test1");
		stringStack.Push("test2");
		stringStack.Push("test3");

		stringStack.Pop();
		REQUIRE(stringStack.GetSize() == 2);
		REQUIRE(!stringStack.IsEmpty());
		REQUIRE(stringStack.GetTop() == "test2");

		stringStack.Pop();
		REQUIRE(stringStack.GetSize() == 1);
		REQUIRE(!stringStack.IsEmpty());
		REQUIRE(stringStack.GetTop() == "test1");

		stringStack.Pop();
		REQUIRE(stringStack.GetSize() == 0);
		REQUIRE(stringStack.IsEmpty());
		REQUIRE_THROWS_AS(stringStack.GetTop(), std::logic_error);

		REQUIRE_THROWS_AS(stringStack.Pop(), std::logic_error);
		REQUIRE(stringStack.GetSize() == 0);
		REQUIRE(stringStack.IsEmpty());
	}

	SECTION("Checl clear method")
	{
		stringStack.Push("test1");
		stringStack.Push("test2");
		stringStack.Push("test3");

		stringStack.Clear();

		REQUIRE(stringStack.GetSize() == 0);
		REQUIRE(stringStack.IsEmpty());
		REQUIRE_THROWS_AS(stringStack.GetTop(), std::logic_error);
	}
}

TEST_CASE("Check copy constructor appropriate operator=")
{
	StringStack firstStack;
	StringStack secondStack;

	firstStack.Push("test1");
	firstStack.Push("test2");
	firstStack.Push("test3");

	SECTION("Copy to secondStack")
	{
		secondStack = firstStack;

		REQUIRE(secondStack.GetSize() == 3);
		REQUIRE(!secondStack.IsEmpty());
		REQUIRE(secondStack.GetTop() == "test3");

		REQUIRE(firstStack.GetSize() == 3);
		REQUIRE(!firstStack.IsEmpty());
		REQUIRE(firstStack.GetTop() == "test3");
	}

	SECTION("Work with second stack won't change first stack")
	{
		secondStack = firstStack;

		secondStack.Push("test4");

		REQUIRE(secondStack.GetSize() == 4);
		REQUIRE(!secondStack.IsEmpty());
		REQUIRE(secondStack.GetTop() == "test4");

		REQUIRE(firstStack.GetSize() == 3);
		REQUIRE(!firstStack.IsEmpty());
		REQUIRE(firstStack.GetTop() == "test3");
	}

	SECTION("Check that second stack is the exact copy of first")
	{
		secondStack = firstStack;

		REQUIRE(secondStack.GetSize() == 3);
		REQUIRE(!secondStack.IsEmpty());
		REQUIRE(secondStack.GetTop() == "test3");

		secondStack.Pop();
		REQUIRE(secondStack.GetSize() == 2);
		REQUIRE(!secondStack.IsEmpty());
		REQUIRE(secondStack.GetTop() == "test2");

		secondStack.Pop();
		REQUIRE(secondStack.GetSize() == 1);
		REQUIRE(!secondStack.IsEmpty());
		REQUIRE(secondStack.GetTop() == "test1");

		secondStack.Pop();
		REQUIRE(secondStack.GetSize() == 0);
		REQUIRE(secondStack.IsEmpty());
		REQUIRE_THROWS_AS(secondStack.GetTop(), std::logic_error);

		REQUIRE_THROWS_AS(secondStack.Pop(), std::logic_error);
		REQUIRE(secondStack.GetSize() == 0);
		REQUIRE(secondStack.IsEmpty());

		REQUIRE(firstStack.GetSize() == 3);
		REQUIRE(!firstStack.IsEmpty());
		REQUIRE(firstStack.GetTop() == "test3");
	}
}

TEST_CASE("Check move constructor and appropriate operator=")
{
	StringStack firstStack;
	StringStack secondStack;

	firstStack.Push("test1");
	firstStack.Push("test2");
	firstStack.Push("test3");

	secondStack = std::move(firstStack);

	SECTION("first stack should be removed")
	{
		REQUIRE_THROWS_AS(firstStack.Pop(), std::logic_error);
		REQUIRE(firstStack.GetSize() == 0);
		REQUIRE(firstStack.IsEmpty());
	}

	SECTION("second stack should be first stack")
	{
		REQUIRE(secondStack.GetSize() == 3);
		REQUIRE(!secondStack.IsEmpty());
		REQUIRE(secondStack.GetTop() == "test3");
	}
}