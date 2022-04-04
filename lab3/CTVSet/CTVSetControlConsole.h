#pragma once
#include <string>
#include <iostream>
#include "CTVSet.h"
class CTVSetControlConsole
{
public:
	CTVSetControlConsole(std::istream& inputStream, std::ofstream& outputStream, CTVSet& TVSet);
	void StartSession();

private:
	const int NoChannel = 0;

	enum class Command
	{
		TurnOn,
		TurnOff,
		SelectChannel,
		Info,
		Exit,
		Skip,
	};

	Command GetCommand();
	bool ParseCommand(std::string& inputCommand, Command& command, int& argument);

	std::istream& m_inputStream;
	std::ofstream& m_outputStream;
	CTVSet& m_TVSet;
};

