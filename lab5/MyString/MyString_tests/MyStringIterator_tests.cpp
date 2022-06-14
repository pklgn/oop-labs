#pragma once
#include "../MyString.h"
#include "../MyStringIterator.hpp"
#include "../../../catch2/catch.hpp"

TEST_CASE("Check iterator const version")
{
	const MyString exampleStr("Country roads, take me home");

	SECTION("Check begin and end const iterator methods")
	{
		MyString::const_iterator beginIt = exampleStr.begin();
		const char* firstLetterPtr = exampleStr.GetStringData();
		REQUIRE(beginIt == firstLetterPtr);

		MyString::const_iterator endIt = exampleStr.end();
		REQUIRE(endIt == firstLetterPtr + exampleStr.GetLength());
	}
}

TEST_CASE("Check iterator operators")
{
	std::string stlString("All my memories\0, gather around her");
	const MyString exampleStr(stlString);
	SECTION("Check operator*")
	{
		MyString::const_iterator beginIt = exampleStr.begin();
		REQUIRE(*beginIt == 'A');

		MyString::const_iterator endIt = exampleStr.end();
		REQUIRE(*endIt == '\0');
	}

	SECTION("Check operator++")
	{
		MyString::const_iterator it = exampleStr.begin();
		for (size_t i = 0; i < 5; ++i, ++it)
		{
			REQUIRE(exampleStr[i] == *it);
		}

		REQUIRE(*it == 'y');
	}

	SECTION("Check operator--")
	{
		MyString::const_iterator it = exampleStr.end();
		REQUIRE(*it == '\0');
		--it;

		for (size_t i = exampleStr.GetLength() - 1; i > 0; --i, --it)
		{
			REQUIRE(exampleStr[i] == *it);
		}

		REQUIRE(*it == 'A');
	}

	SECTION("Check operator+=")
	{
		MyString::const_iterator it = exampleStr.begin();

		REQUIRE(*it == 'A');

		it += 1;
		REQUIRE(*it == 'l');

		it += 2;
		REQUIRE(*it == ' ');

		it += 4;
		REQUIRE(*it == 'm');
	}

	SECTION("Check operator-=")
	{
		MyString::const_iterator it = exampleStr.end();

		REQUIRE(*it == '\0');

		it -= 1;
		REQUIRE(*it == 's');

		it -= 2;
		REQUIRE(*it == 'i');

		it -= 3;
		REQUIRE(*it == 'm');
	}

	SECTION("Check operator-")
	{
		MyString::const_iterator beginIt = exampleStr.begin();
		MyString::const_iterator endIt = exampleStr.end();

		REQUIRE(endIt - beginIt == exampleStr.GetLength());

		--endIt;
		REQUIRE(endIt - beginIt == exampleStr.GetLength() - 1);

		++beginIt;
		REQUIRE(endIt - beginIt == exampleStr.GetLength() - 2);
	}

	SECTION("Check operator<")
	{
		MyString::const_iterator beginIt = exampleStr.begin();
		MyString::const_iterator endIt = exampleStr.end();

		REQUIRE(beginIt < endIt);
		REQUIRE(!(endIt < beginIt));

		beginIt += exampleStr.GetLength();
		REQUIRE(!(beginIt < endIt));
	}

	SECTION("Check operator>")
	{
		MyString::const_iterator beginIt = exampleStr.begin();
		MyString::const_iterator endIt = exampleStr.end();

		REQUIRE(endIt > beginIt);
		REQUIRE(!(beginIt > endIt));

		beginIt += exampleStr.GetLength();
		REQUIRE(!(beginIt > endIt));
	}

	SECTION("Check operator<=")
	{
		MyString::const_iterator beginIt = exampleStr.begin();
		MyString::const_iterator endIt = exampleStr.end();

		REQUIRE(beginIt <= endIt);

		beginIt += exampleStr.GetLength();
		REQUIRE(beginIt <= endIt);
	}

	SECTION("Check operator>=")
	{
		MyString::const_iterator beginIt = exampleStr.begin();
		MyString::const_iterator endIt = exampleStr.end();

		REQUIRE(endIt >= beginIt);

		beginIt += exampleStr.GetLength();
		REQUIRE(beginIt >= endIt);
	}

	SECTION("Check operator[]")
	{
		MyString::const_iterator beginIt = exampleStr.begin();
		MyString::const_iterator endIt = exampleStr.end();

		REQUIRE(beginIt[0] == 'A');
		REQUIRE(beginIt[1] == 'l');
		REQUIRE(beginIt[2] == 'l');
		REQUIRE(beginIt[3] == ' ');
		REQUIRE(beginIt[4] == 'm');
		REQUIRE(beginIt[5] == 'y');

		REQUIRE(endIt[0] == '\0');
		REQUIRE(endIt[-1] == 's');
		REQUIRE(endIt[-2] == 'e');
	}
}

TEST_CASE("Check not const iterator")
{
	MyString exampleStr("Dark and dusty, painted on the sky");

	SECTION("Check begin and end not const iterator methods")
	{
		MyString::const_iterator beginIt = exampleStr.begin();
		const char* firstLetterPtr = exampleStr.GetStringData();
		REQUIRE(beginIt == firstLetterPtr);

		MyString::const_iterator endIt = exampleStr.end();
		REQUIRE(endIt == firstLetterPtr + exampleStr.GetLength());
	}
}

TEST_CASE("Check operators for not const iterator")
{
	MyString exampleStr("Misty taste of moonshine, teardrop in my eye");

	SECTION("Check operator= from begin")
	{
		MyString::iterator it = exampleStr.begin();

		REQUIRE(*it == 'M');

		*it = 'm';
		REQUIRE(exampleStr == "misty taste of moonshine, teardrop in my eye");

		it += 15;
		REQUIRE(*it == 'm');

		*it = 's';

		*it++;
		*it = 'u';

		*++it;
		*it = 'n';

		*++it;
		*it = ' ';

		REQUIRE(exampleStr == "misty taste of sun shine, teardrop in my eye");
	}

	SECTION("Check operator= from end")
	{
		MyString::iterator it = exampleStr.end();

		REQUIRE(*it == '\0');

		*it--;
		*it = '.';

		*it--;
		*it = '!';

		*--it;
		*it = '?';

		REQUIRE(exampleStr == "Misty taste of moonshine, teardrop in my ?!.");

		MyString::iterator it2 = exampleStr.end();
		it2 -= 20;
		*it2 = 's';
		REQUIRE(exampleStr == "Misty taste of moonshines teardrop in my ?!.");
	}

	SECTION("Check operator<")
	{
		MyString::iterator beginIt = exampleStr.begin();
		MyString::iterator endIt = exampleStr.end();

		REQUIRE(beginIt < endIt);
		REQUIRE(!(endIt < beginIt));

		beginIt += exampleStr.GetLength();
		REQUIRE(!(beginIt < endIt));
	}

	SECTION("Check operator>")
	{
		MyString::iterator beginIt = exampleStr.begin();
		MyString::iterator endIt = exampleStr.end();

		REQUIRE(endIt > beginIt);
		REQUIRE(!(beginIt > endIt));

		beginIt += exampleStr.GetLength();
		REQUIRE(!(beginIt > endIt));
	}

	SECTION("Check operator<=")
	{
		MyString::iterator beginIt = exampleStr.begin();
		MyString::iterator endIt = exampleStr.end();

		REQUIRE(beginIt <= endIt);

		beginIt += exampleStr.GetLength();
		REQUIRE(beginIt <= endIt);
	}

	SECTION("Check operator>=")
	{
		MyString::iterator beginIt = exampleStr.begin();
		MyString::iterator endIt = exampleStr.end();

		REQUIRE(endIt >= beginIt);

		beginIt += exampleStr.GetLength();
		REQUIRE(beginIt >= endIt);
	}

	SECTION("Check operator[]")
	{
		MyString::iterator beginIt = exampleStr.begin();
		MyString::iterator endIt = exampleStr.end();

		REQUIRE(beginIt[0] == 'M');
		beginIt[0] = 'm';
		REQUIRE(beginIt[2] == 's');

		REQUIRE(endIt[-1] == 'e');
		endIt[-2] = 'e';

		REQUIRE(exampleStr == "misty taste of moonshine, teardrop in my eee");
	}
}

TEST_CASE("Check reverse iterator")
{
	MyString exampleStr("Country roads, take me home");

	SECTION("Check const reverse iterator")
	{
		MyString::const_reverse_iterator rIt = exampleStr.rend() - 1;
		for (size_t i = 0; i < exampleStr.GetLength(); ++i, --rIt)
		{
			REQUIRE(exampleStr[i] == *rIt);
		}

		MyString::const_reverse_iterator rBeginIt = exampleStr.rbegin();
		REQUIRE(*rBeginIt == 'e');

		++rBeginIt;
		REQUIRE(*rBeginIt == 'm');

		++rBeginIt;
		REQUIRE(*rBeginIt == 'o');

		++rBeginIt;
		REQUIRE(*rBeginIt == 'h');

		MyString::const_reverse_iterator rEndIt = exampleStr.rend() - 1;
		REQUIRE(*rEndIt == 'C');

		--rEndIt;
		REQUIRE(*rEndIt == 'o');

		----rEndIt;
		REQUIRE(*rEndIt == 'n');
	}
}

TEST_CASE("Check range based for version")
{
	MyString exampleStr("Life is old there, older than the trees");

	SECTION("Replace all spaces with _")
	{
		for (char& ch: exampleStr)
		{
			if (isspace(ch))
			{
				ch = '_';
			}
		}

		REQUIRE(exampleStr == "Life_is_old_there,_older_than_the_trees");
	}
}