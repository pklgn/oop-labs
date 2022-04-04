#pragma once
#include <string>
#include <iostream>
#include "CTVSet.h"
class CTVSetControlConsole
{
public:
	CTVSetControlConsole(std::istream& inputStream, std::ostream& outputStream, CTVSet& TVSet);
	void ProcessSession();

private:
	const int NoChannel = 0;

	enum class CommandName
	{
		TurnOn,
		TurnOff,
		SelectChannel,
		Info,
		Exit,
		Skip,
	};

	struct Command
	{
		CommandName name;
		int argument;
	};

	Command GetCommand();
	bool ParseCommand(std::string& inputCommand, Command& command);
	void PrintTVSetInfo();

	std::istream& m_inputStream;
	std::ostream& m_outputStream;
	CTVSet& m_TVSet;
};

