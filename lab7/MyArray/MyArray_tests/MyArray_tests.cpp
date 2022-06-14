#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MyArray.hpp"
#include <string>

TEST_CASE("Work with std::string")
{
	SECTION("Check default values")
	{
		MyArray<std::string, 2> stringArr;
		REQUIRE(stringArr.GetSize() == 2);
	}

}