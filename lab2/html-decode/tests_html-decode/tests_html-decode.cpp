#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "html_decode.h"
#include <iostream>

//выделить функцию для тестирования, которая принимает исходную строку
SCENARIO("Input stream contains appropriate values")
{
	std::vector<double> numbers;
	std::ostringstream outputStream;
	WHEN("There is no value to decode")
	{
		std::istringstream inputStream("A simple text");
		std::ostringstream outputStream;
		HtmlTextDecode(inputStream, outputStream);
		REQUIRE(outputStream.str() == "A simple text\n");
	}

	WHEN("There is an empty string")
	{
		std::istringstream inputStream("");
		std::ostringstream outputStream;
		HtmlTextDecode(inputStream, outputStream);
		REQUIRE(outputStream.str() == "\n");
	}

	WHEN("There is one html value")
	{
		std::istringstream inputStream("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;");
		std::ostringstream outputStream;
		HtmlTextDecode(inputStream, outputStream);
		REQUIRE(outputStream.str() == "Cat <says> \"Meow\". M&M'\n");
	}

	WHEN("Several html entities in a row")
	{
		std::istringstream inputStream("&lt;&lt;&lt;&lt;&gt&gt&quot;&amp;&apos;");
		std::ostringstream outputStream;
		HtmlTextDecode(inputStream, outputStream);
		REQUIRE(outputStream.str() == "<<<<>>\"&'\n");
	}

	WHEN("Several html entities in a row with extra character")
	{
		std::istringstream inputStream("&lt;&lt;&lt;&lt;&gt&gt&quot;&amp;&apos1;");
		std::ostringstream outputStream;
		HtmlTextDecode(inputStream, outputStream);
		REQUIRE(outputStream.str() == "<<<<>>\"&'1;\n");
	}

	WHEN("There are several html entities and only one semicolon")
	{
		std::istringstream inputStream("&lt;&quot");
		std::ostringstream outputStream;
		HtmlTextDecode(inputStream, outputStream);
		REQUIRE(outputStream.str() == "<&quot\n");
	}

	WHEN("There are several html entities and only one semicolon")
	{
		std::istringstream inputStream("&lt;&quot");
		std::ostringstream outputStream;
		HtmlTextDecode(inputStream, outputStream);
		REQUIRE(outputStream.str() == "<&quot\n");
	}

	WHEN("There are several html entities and only one semicolon")
	{
		std::istringstream inputStream("&lt&quot;");
		std::ostringstream outputStream;
		HtmlTextDecode(inputStream, outputStream);
		REQUIRE(outputStream.str() == "&lt\"\n");
	}
}
