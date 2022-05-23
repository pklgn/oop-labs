#pragma once
#define CATCH_CONFIG_MAIN
#include "../MyString.h"
#include "../../../catch2/catch.hpp"

TEST_CASE("Construct object with zero parametres")
{
	MyString str;
	REQUIRE(str.GetLength() == 0);
}

TEST_CASE("Construct parametrized object")
{
	SECTION("Use pointer to char without length")
	{
		std::string cStr("test");
		MyString str(cStr.c_str());
		REQUIRE(str.GetLength() == 4);
		REQUIRE(str.GetStringData() == cStr);

		std::string emptyCStr("");
		MyString emptyStr(emptyCStr.c_str());
		REQUIRE(emptyStr.GetLength() == 0);
		REQUIRE(emptyStr.GetStringData() == emptyCStr);
	}

	SECTION("Use pointer to char with length")
	{
		std::string cStr("quite a long string for the test");
		MyString str(cStr.c_str(), 31);
		REQUIRE(str.GetLength() == 31);
		REQUIRE(str.GetStringData() == cStr.substr(0, 31));

		MyString copyStr(cStr.c_str(), 32);
		REQUIRE(copyStr.GetLength() == 32);
		REQUIRE(copyStr.GetStringData() == cStr);

		MyString extraStr(cStr.c_str(), 33);
		REQUIRE(extraStr.GetLength() == 33);
		REQUIRE(extraStr.GetStringData() == cStr);

		std::string emptyCStr("");
		MyString emptyStr(emptyCStr.c_str(), 0);
		REQUIRE(emptyStr.GetLength() == 0);
		REQUIRE(emptyStr.GetStringData() == emptyCStr);

		std::string zeroCStr("zero\0symbol\0among\0text");
		MyString zeroStr(zeroCStr.c_str(), 22);
		REQUIRE(zeroStr.GetLength() == 22);
		REQUIRE(zeroStr.GetStringData() == zeroCStr);
	}

	SECTION("Use std::string as parameter")
	{
		std::string str("test string");
		MyString myStr(str);
		REQUIRE(myStr.GetLength() == str.size());
		REQUIRE(myStr.GetStringData() == str);

		std::string emptyStr("");
		MyString emptyMyStr(emptyStr);
		REQUIRE(emptyMyStr.GetLength() == emptyStr.size());
		REQUIRE(emptyMyStr.GetStringData() == emptyStr);
	}

	SECTION("Use copy constructor")
	{
		std::string testStr("test");
		MyString myStr1(testStr);
		MyString myStr2(myStr1);

		REQUIRE(myStr1 == myStr2);
	}

	SECTION("Check moving constructor")
	{
		std::string emptyStr;
		std::string testStr("test");
		MyString myStr1(testStr);
		MyString myStr2(std::move(myStr1));

		REQUIRE(myStr1.GetLength() == 0);
	}
}

TEST_CASE("Use string operator")
{
	SECTION("Use operator =")
	{
		std::string str("SomeString");
		MyString s(str);
		s = s;
		REQUIRE(s == str);
		REQUIRE(s.GetLength() == 10);
		
		std::string emptyStr("");
		MyString s1(emptyStr);
		std::string simpleStr("Not empty string");
		MyString s2(simpleStr);
		s1 = s2;
		REQUIRE(s1 == simpleStr);
		REQUIRE(s1.GetLength() == simpleStr.size());
	}

	SECTION("Use operator +")
	{
		std::string testString("abcde");
		MyString myStr(testString);
		MyString doubleMyStr = myStr + myStr;

		REQUIRE(doubleMyStr.GetLength() == testString.size() * 2);
		REQUIRE(doubleMyStr.GetStringData() == testString + testString);

		MyString tripleMyStr = doubleMyStr + testString;
		REQUIRE(tripleMyStr.GetLength() == testString.size() * 3);
		REQUIRE(tripleMyStr.GetStringData() == testString + testString + testString);

		MyString quadMyStr = tripleMyStr + testString.c_str();
		REQUIRE(quadMyStr.GetLength() == testString.size() * 4);
		REQUIRE(quadMyStr.GetStringData() == testString + testString + testString + testString);
	}

	SECTION("Use operator == or !=")
	{
		std::string string1("string1");
		std::string string2("string2");
		std::string string3("string1");

		REQUIRE(string1 == string1);
		REQUIRE(string1 == string3);
		REQUIRE(string1 != string2);

	}

	SECTION("Use operator < > <= >=")
	{
		std::string s1("small");
		std::string s2("smaller");

		REQUIRE(s1 < s2);
		REQUIRE(!(s1 < s1));
		REQUIRE(s1 <= s1);
		REQUIRE(s2 > s1);

		std::string emptyS("");
		REQUIRE(s1 > emptyS);
		REQUIRE(emptyS >= emptyS);
		REQUIRE(s2 >= s1);
	}

	SECTION("Use operator []")
	{
		std::string str("test string");
		REQUIRE(str[0] == 't');
		REQUIRE(str[4] == ' ');
		REQUIRE(str[11] == 0);

		str[0] = str[1];
		REQUIRE(str[0] == str[1]);
	}

	SECTION("Use >> and << operators")
	{
		std::string testStr("test");
		std::istringstream inputStream("test test");
		MyString myString;
		inputStream >> myString;
		REQUIRE(myString.GetStringData() == testStr);

		std::ostringstream outputStream;
		outputStream << myString;
		REQUIRE(outputStream.str() == "test");
	}
}

TEST_CASE("Check MyString methods")
{
	SECTION("Use Clear()")
	{
		std::string emptyStr;
		MyString testStr("string");
		testStr.Clear();
		
		REQUIRE(testStr.GetLength() == 0);
		REQUIRE(testStr.GetStringData() == emptyStr);
	}

	SECTION("Use substring")
	{
		std::string resultStr("str");
		MyString testStr("string");
		MyString subStr = testStr.SubString(0, 3);

		REQUIRE(subStr.GetLength() == 3);
		REQUIRE(subStr.GetStringData() == resultStr);
	}
}

