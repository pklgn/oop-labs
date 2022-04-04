#include "CTVSetControlConsole.h"
#include <regex>

CTVSetControlConsole::CTVSetControlConsole(std::istream& inputStream, std::ofstream& outputStream, CTVSet& TVSet)
	: m_inputStream(inputStream)
	, m_outputStream(outputStream)
	, m_TVSet(TVSet)

{
}

void CTVSetControlConsole::StartSession()
{
	bool isRunning = true;

	while (isRunning)
	{
		const std::string command = GetCommand();	
	}
}

bool CTVSetControlConsole::ParseCommand(std::string& inputCommand, Command& command, int& argument)
{
	std::cmatch result;
	std::regex regular(R"(([\w]+)?[\s]?+([\d]+)?)");

	if (!regex_match(inputCommand.c_str(), result, regular))
	{
		return false;
	}

	if (result[1].str().empty())
	{
		command = Command::Skip;

		return true;
	}

	if (result[2].str().empty())
	{
		argument = 0;
	}
	else 
	{
		argument = std::stoi(result[2].str());
	}

	if (result[1].str() == "Info")
	{
		command = Command::Info;
	}
	else if (result[1].str() == "TurnOn")
	{
		command = Command::TurnOn;
	}
	else if (result[1].str() == "TurnOff")
	{
		command = Command::TurnOff;
	}
	else if (result[1].str() == "SelectChannel")
	{
		command = Command::SelectChannel;
	}
	else
	{
		command = Command::Skip;
	}

	return true;
}

CTVSetControlConsole::Command CTVSetControlConsole::GetCommand()
{
	int argument;
	Command command;
	std::string inputCommand;
	std::getline(m_inputStream, inputCommand);
	bool isCorrect = ParseCommand(inputCommand, command, argument);
	if (!isCorrect)
	{
		return Command::Skip;
	}
	
	return command;
}