#define CATCH_CONFIG_MAIN
#include "../CTVSet_lib/CTVSet.h"
#include "../CTVSet_lib/CTVSetControlConsole.h"
#include "../../../catch2/catch.hpp"
#include <sstream>

SCENARIO("Separate methods works properly")
{
	CTVSet TVSet;
	std::istringstream inputStream;
	std::ostringstream outputStream;
	CTVSetControlConsole controlConsole(inputStream, outputStream, TVSet);
	WHEN("Print info about new CTVSet instance")
	{
		THEN("All values will be default")
		{
			REQUIRE(TVSet.GetChannel() == 1);
			REQUIRE(!TVSet.IsTurnedOn());
		}
	}

	WHEN("Change channel to not working TVSet")
	{
		TVSet.SetChannel(2);
		THEN("All values will not change")
		{
			REQUIRE(TVSet.GetChannel() == 1);
			REQUIRE(!TVSet.IsTurnedOn());
		}
	}

	WHEN("Turning TVSet On")
	{
		TVSet.TurnOn();
		THEN("TVSet state will change")
		{
			REQUIRE(TVSet.IsTurnedOn());
		}
	}
	WHEN("Change channel on working TVSet")
	{
		TVSet.SetChannel(2);
		THEN("TVSet state will change")
		{
			REQUIRE(TVSet.GetChannel() == 2);
		}
	}
}