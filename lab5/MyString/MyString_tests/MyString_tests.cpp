#pragma once
#define CATCH_CONFIG_MAIN
#include "../MyString.h"
#include "../../../catch2/catch.hpp"

TEST_CASE("Construct object with zero parametres")
{
	MyString str;
	REQUIRE(str.GetLength() == 0);
	REQUIRE(str.GetStringData() == std::string());
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

		std::string cStrDivided("test\0test1\0test2");
		MyString strDivided(cStrDivided.c_str());
		REQUIRE(strDivided.GetLength() == 4);
		REQUIRE(strDivided.GetStringData() == cStr);
	}

	SECTION("Use pointer to char with length")
	{
		// TODO: добавить тест с substr не с нулевого символа
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

		// TODO: добавить в тесты каждого метода тесты с нулевыми символами
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

		std::string strDivided("test\0string\0");
		MyString myStrDivided(strDivided);
		REQUIRE(myStrDivided.GetLength() == strDivided.size());
		REQUIRE(myStrDivided.GetStringData() == strDivided);
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

		std::string strDivided("Divided\0by\0");
		MyString sDivided(strDivided);
		MyString sDividedEqual;
		sDividedEqual = sDivided;
		REQUIRE(sDivided == sDividedEqual);
		REQUIRE(sDivided.GetLength() == sDividedEqual.GetLength());
	}

	SECTION("Use operator +")
	{
		// TODO: ƒописать тест дл€ вы€влени€ выхода за границы строки
		std::string testString("abc\0e");
		MyString myStr(testString);
		MyString doubleMyStr = myStr + myStr;

		REQUIRE(doubleMyStr.GetLength() == testString.size() * 2);
		REQUIRE(doubleMyStr.GetStringData() == testString + testString);

		MyString tripleMyStr = doubleMyStr + testString;
		REQUIRE(tripleMyStr.GetLength() == testString.size() * 3);
		REQUIRE(tripleMyStr.GetStringData() == testString + testString + testString);

		MyString tripleMyStr2 = testString + doubleMyStr;
		REQUIRE(tripleMyStr2.GetLength() == testString.size() * 3);
		REQUIRE(tripleMyStr2.GetStringData() == testString + testString + testString);

		MyString quadMyStr = tripleMyStr + testString.c_str();
		REQUIRE(quadMyStr.GetLength() == testString.size() * 4);
		REQUIRE(quadMyStr.GetStringData() == testString + testString + testString + testString);

		MyString quadMyStr2 = testString.c_str() + tripleMyStr;
		REQUIRE(quadMyStr2.GetLength() == testString.size() * 4);
		REQUIRE(quadMyStr2.GetStringData() == testString + testString + testString + testString);
	}

	SECTION("Use operator == or !=")
	{
		MyString string1("string1");
		MyString string2("string2");
		MyString string3("string1");

		REQUIRE(string1 == string1);
		REQUIRE(string1 == string3);
		REQUIRE(string1 != string2);

		MyString stringDivided("string\0divided");
		REQUIRE(stringDivided == stringDivided);
		REQUIRE(stringDivided != string1);
	}

	SECTION("Use operator < > <= >=")
	{
		MyString s1("small");
		MyString s2("smaller");
		MyString s3("small\0\0");

		REQUIRE(s1 <= s2);
		REQUIRE(s1 < s2);
		REQUIRE(!(s1 < s1));
		REQUIRE(s1 <= s1);
		REQUIRE(s2 > s1);

		MyString emptyS("");
		REQUIRE(s1 > emptyS);
		REQUIRE(emptyS >= emptyS);
		REQUIRE(s2 >= s1);

		REQUIRE(s1 <= s3);
		REQUIRE(s2 > s3);
	}

	SECTION("Use operator []")
	{
		std::string stlString("test string");
		MyString str(stlString.c_str());
		REQUIRE(str[0] == 't');
		REQUIRE(str[4] == ' ');
		REQUIRE(str[10] == 'g');
		REQUIRE_THROWS_AS(str[11], std::out_of_range);

		str[0] = str[1];
		REQUIRE(str[0] == str[1]);
	}

	SECTION("Use >> and << operators")
	{
		std::string testStr("test");
		std::istringstream inputStream("test cast1");
		MyString myString;
		inputStream >> myString;
		REQUIRE(myString.GetStringData() == testStr);

		MyString failStreamMyString;
		inputStream.setstate(std::ios::failbit);
		inputStream >> failStreamMyString;
		REQUIRE(failStreamMyString.GetLength() == 0);

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
		MyString resultStr1("str");
		MyString testStr("string");
		MyString subStr1 = testStr.SubString(0, 3);

		// TODO: ќтобразить все 4 кейса копировани€ 

		REQUIRE(subStr1.GetLength() == 3);
		REQUIRE(subStr1 == resultStr1);

		MyString subStr2 = testStr.SubString(1, 2);
		MyString resultStr2("tr");
		REQUIRE(subStr2.GetLength() == 2);
		REQUIRE(subStr2 == resultStr2);

		MyString subStr3 = testStr.SubString(1, 10);
		MyString resultStr3("tring");
		REQUIRE(subStr3.GetLength() == 5);
		REQUIRE(subStr3 == resultStr3);

		MyString subStr4 = testStr.SubString(10, 1);
		MyString resultStr4;
		REQUIRE(subStr4.GetLength() == 0);
		REQUIRE(subStr4 == resultStr4);

		MyString subStr5 = testStr.SubString(10, 0);
		MyString resultStr5;
		REQUIRE(subStr5.GetLength() == 0);
		REQUIRE(subStr5 == resultStr5);

	}
}
// TODO: добавить except range
