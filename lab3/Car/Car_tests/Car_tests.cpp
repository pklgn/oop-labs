#define CATCH_CONFIG_MAIN
#include "../Car_lib/Car.h"
#include "../Car_lib/CarControlConsole.h"
#include "../../../catch2/catch.hpp"
#include <sstream>

SCENARIO("Car class works properly")
{
	Car car;
	WHEN("Car has just created")
	{
		THEN("Engine will be off")
		{
			REQUIRE(!car.IsTurnedOn());
		}
		THEN("Speed will be equal to 0")
		{
			REQUIRE(car.GetSpeed() == 0);
		}
		THEN("Gear will be neutral and equal to 0")
		{
			REQUIRE(car.GetGear() == 0);
		}
		THEN("Direction will be in place")
		{
			REQUIRE(car.GetDirection() == Car::Direction::InPlace);
		}
	}

	WHEN("Trying to turn off engine that is not running")
	{
		car.TurnOffEngine();
		THEN("The engine will be off")
		{
			REQUIRE(!car.IsTurnedOn());
		}
	}

	WHEN("Turn the engine on which is not running")
	{
		car.TurnOnEngine();
		THEN("The engine will be on")
		{
			REQUIRE(car.IsTurnedOn());
		}
	}

	WHEN("Turn the engine on which is running")
	{
		car.TurnOnEngine();
		car.TurnOnEngine();
		THEN("The engine will be also on")
		{
			REQUIRE(car.IsTurnedOn());
		}
	}

	WHEN("Set the first gear from neutral")
	{
		car.TurnOnEngine();
		THEN("The gear will be first")
		{
			REQUIRE(car.SetGear(1));
			REQUIRE(car.GetGear() == 1);
		}
	}

	WHEN("Set the first gear from neutral and moving forward")
	{
		car.TurnOnEngine();
		THEN("The gear will be first")
		{
			REQUIRE(car.SetGear(1));
			REQUIRE(car.SetSpeed(15));
			REQUIRE(car.GetSpeed() == 15);
			REQUIRE(car.GetDirection() == Car::Direction::Forwards);
		}
	}
	
	WHEN("Try to turn engine off while moving")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(15);
		car.TurnOffEngine();
		THEN("Engine will be running")
		{
			REQUIRE(car.IsTurnedOn());
		}
	}

	WHEN("Try to switch gear to -1 while moving forwards")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(15);
		car.SetGear(-1);
		THEN("Gear will not change")
		{
			REQUIRE(car.GetGear() == 1);
		}
	}

	WHEN("Try to switch gear to 5 while moving forwards with not proper speed")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(15);
		car.SetGear(5);
		THEN("Gear will not change")
		{
			REQUIRE(car.GetGear() == 1);
		}
	}

	WHEN("Try to accelerate too much for first gear")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(31);
		THEN("Speed will not change")
		{
			REQUIRE(car.GetSpeed() == 0);
		}
	}

	WHEN("Try to accelerate enough to switch gear")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(2);
		THEN("Gear will change")
		{
			REQUIRE(car.GetSpeed() == 30);
			REQUIRE(car.GetGear() == 2);
		}
	}

	WHEN("Try to switch non-existent gear")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(30);
		car.SetGear(6);
		THEN("Nothing will change")
		{
			REQUIRE(car.GetSpeed() == 30);
			REQUIRE(car.GetGear() == 1);
		}
	}

	WHEN("Try to switch gear to reverse")
	{
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		THEN("Direction will be backwards")
		{
			REQUIRE(car.GetSpeed() == 10);
			REQUIRE(car.GetGear() == -1);
			REQUIRE(car.GetDirection() == Car::Direction::Backwards);
		}
	}

	WHEN("Try to switch gear to reverse while moving")
	{
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(10);
		car.SetGear(-1);
		THEN("Gear will not change")
		{
			REQUIRE(car.GetSpeed() == 10);
			REQUIRE(car.GetGear() == 1);
			REQUIRE(car.GetDirection() == Car::Direction::Forwards);
		}
	}

	WHEN("Move backwards with neutral gear and try to switch to reverse gear")
	{
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(0);
		car.SetGear(-1);
		THEN("Gear will not change")
		{
			REQUIRE(car.GetSpeed() == 10);
			REQUIRE(car.GetGear() == 0);
			REQUIRE(car.GetDirection() == Car::Direction::Backwards);
		}
	}

	WHEN("Move backwards with reverse gear and try to switch to first gear")
	{
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(1);
		THEN("Gear will not change")
		{
			REQUIRE(car.GetSpeed() == 10);
			REQUIRE(car.GetGear() == -1);
			REQUIRE(car.GetDirection() == Car::Direction::Backwards);
		}

		car.SetSpeed(0);
		car.SetGear(1);
		THEN("Gear will change")
		{
			REQUIRE(car.GetSpeed() == 0);
			REQUIRE(car.GetGear() == 1);
			REQUIRE(car.GetDirection() == Car::Direction::InPlace);
		}
	}

	WHEN("Move backwards with neutral gear and try to switch to first gear")
	{
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		car.SetGear(0);
		car.SetGear(1);
		THEN("Gear will not change")
		{
			REQUIRE(car.GetSpeed() == 10);
			REQUIRE(car.GetGear() == 0);
			REQUIRE(car.GetDirection() == Car::Direction::Backwards);
		}

		THEN("Gear will change")
		{
			REQUIRE(car.SetSpeed(0));
			REQUIRE(car.SetGear(1));
			REQUIRE(car.GetGear() == 1);
		}
	}
	WHEN("Try to set negative speed")
	{
		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(5);
		THEN("Speed will not change")
		{
			REQUIRE(!car.SetSpeed(-10));
			REQUIRE(car.GetSpeed() == 5);
		}
	}
	WHEN("Try to switch all correct gears")
	{
		car.TurnOnEngine();
		THEN("Gears will change")
		{
			REQUIRE(car.SetGear(-1));
			REQUIRE(car.SetSpeed(10));
			REQUIRE(car.GetSpeed() == 10);
			REQUIRE(car.GetDirection() == Car::Direction::Backwards);
			REQUIRE(car.SetSpeed(0));
			REQUIRE(car.GetDirection() == Car::Direction::InPlace);
			REQUIRE(car.SetGear(1));
			REQUIRE(car.SetSpeed(20));
			REQUIRE(car.GetDirection() == Car::Direction::Forwards);
			REQUIRE(car.SetGear(2));
			REQUIRE(car.SetSpeed(45));
			REQUIRE(car.SetGear(3));
			REQUIRE(car.SetSpeed(50));
			REQUIRE(car.SetGear(4));
			REQUIRE(car.SetSpeed(80));
			REQUIRE(car.SetGear(5));
			REQUIRE(car.SetSpeed(150));
			REQUIRE(car.GetSpeed() == 150);
		}
	}

	WHEN("Try to slow down on neutral gear moving backwards")
	{
		car.TurnOnEngine();
		THEN("Direction will not change")
		{
			REQUIRE(car.SetGear(-1));
			REQUIRE(car.SetSpeed(20));
			REQUIRE(car.GetSpeed() == 20);
			REQUIRE(car.GetDirection() == Car::Direction::Backwards);
			REQUIRE(car.SetGear(0));
			REQUIRE(car.SetSpeed(15));
			REQUIRE(car.GetDirection() == Car::Direction::Backwards);
		}
	}

	WHEN("Try to switch gear from backwards to second")
	{
		car.TurnOnEngine();
		THEN("Direction will not change")
		{
			REQUIRE(car.SetGear(-1));
			REQUIRE(car.SetSpeed(20));
			REQUIRE(!car.SetGear(2));
		}
	}
}

SCENARIO("ControlConsole class works properly")
{
	Car car;
	std::istringstream inputStream;
	std::ostringstream outputStream;
	CarControlConsole console(inputStream, outputStream, car);

	WHEN("Print info for the new car console session")
	{
		inputStream.str("Info\nExit\n");
		const std::string response = "Engine: Off\nDirection: In place\nSpeed: 0\nGear: 0\n";
		THEN("Info will be match to default values of car")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == response);
		}
	}

	WHEN("Printing info for slightly modified car")
	{
		inputStream.str("EngineOn\nInfo\nExit\n");
		const std::string response = "Engine: On\nDirection: In place\nSpeed: 0\nGear: 0\n";
		THEN("Info will be match to values of the car")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == response);
		}
	}

	WHEN("Printing info for modified car")
	{
		inputStream.str("EngineOn\nSetGear 1\nSetSpeed 10\nInfo\nExit\n");
		const std::string response = "Engine: On\nDirection: Forwards\nSpeed: 10\nGear: 1\n";
		THEN("Response will match the Info result")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == response);
		}
	}

	WHEN("Changing to several gears works correctly")
	{
		inputStream.str("EngineOn\nSetGear 1\nSetSpeed 30\nSetGear 2\nInfo\nExit\n");
		const std::string response = "Engine: On\nDirection: Forwards\nSpeed: 30\nGear: 2\n";
		THEN("Response will match the Info result")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == response);
		}
	}

	WHEN("Turning car off when it is not running")
	{
		inputStream.str("Engineoff\nInfo\nExit\n");
		const std::string response = "Engine: Off\nDirection: In place\nSpeed: 0\nGear: 0\n";
		THEN("Response will match default values of the car")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == response);
		}
	}

	WHEN("Passing wrong gear number")
	{
		inputStream.str("EngineOn\nSetGear -1\nSetGear -2\nInfo\nExit\n");
		const std::string response = "Engine: On\nDirection: In place\nSpeed: 0\nGear: -1\n";
		THEN("Response will match previous values")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == response);
		}
	}
}