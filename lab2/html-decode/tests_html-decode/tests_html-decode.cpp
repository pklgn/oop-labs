#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "html_decode.h"
#include <iostream>

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
		REQUIRE(outputStream.str() == "\n");
	}
}
