#pragma once
#include "Car.h"
#include <iostream>
#include <string>
class CarControlConsole
{
public:
	CarControlConsole(std::istream& inputStream, std::ostream& outputStream, Car& car);
	void ProcessSession();

private:
	enum class CommandName
	{
		EngineOn,
		EngineOff,
		SetGear,
		SetSpeed,
		Info,
		Help,
		Exit,
		SkipCommand,
	};

	struct Command
	{
		CommandName name;
		int argument;
	};

	Command GetCommand();
	bool ParseCommand(std::string& inputCommand, Command& command);
	void PrintInfo();
	void PrintHelp();
	void SkipCommand();
	void EngineOn();
	void EngineOff();
	void SetGear(int gear);
	void SetSpeed(int speed);

	std::istream& m_inputStream;
	std::ostream& m_outputStream;
	Car& m_Car;
};
