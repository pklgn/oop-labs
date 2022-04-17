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
}

SCENARIO("Console methods work properly")
{
	CTVSet TVSet;
	WHEN("Requesting info on the new instance of TVSet")
	{
		std::istringstream inputStream("Info\n");
		std::ostringstream outputStream;
		CTVSetControlConsole controlConsole(inputStream, outputStream, TVSet);
		controlConsole.ProcessSession();
		THEN("TVSet will be default")
		{
			REQUIRE(outputStream.str() == "State: Off\nChannel: 1\n");
		}
	}

	WHEN("Turning TVSet on")
	{
		std::istringstream inputStream("TurnOn\n");
		std::ostringstream outputStream;
		CTVSetControlConsole controlConsole(inputStream, outputStream, TVSet);
		controlConsole.ProcessSession();
		THEN("TVSet will be on")
		{
			REQUIRE(outputStream.str() == "State: On\nChannel: 1\n");
		}
	}

	WHEN("Setting channel on TVSet")
	{
		std::istringstream inputStream("SetChannel 2\n");
		std::ostringstream outputStream;
		CTVSetControlConsole controlConsole(inputStream, outputStream, TVSet);
		controlConsole.ProcessSession();
		THEN("TVSet will be on and channel will be equal to 2")
		{
			REQUIRE(outputStream.str() == "State: On\nChannel: 2\n");
		}
	}

	WHEN("Turning TVSet off")
	{
		std::istringstream inputStream("TurnOff\n");
		std::ostringstream outputStream;
		CTVSetControlConsole controlConsole(inputStream, outputStream, TVSet);
		controlConsole.ProcessSession();
		THEN("TVSet will be off and channel will be equal to 2")
		{
			REQUIRE(outputStream.str() == "State: Off\nChannel: 2\n");
		}
	}

	WHEN("Setting channel on TVSet which was turned off")
	{
		std::istringstream inputStream("SetChannel 42\n");
		std::ostringstream outputStream;
		CTVSetControlConsole controlConsole(inputStream, outputStream, TVSet);
		controlConsole.ProcessSession();
		THEN("TVSet will be off and channel will be equal to 2")
		{
			REQUIRE(outputStream.str() == "State: On\nChannel: 2\n");
		}
	}
}