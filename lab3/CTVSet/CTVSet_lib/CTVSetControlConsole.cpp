#include "pch.h"
#include "CTVSetControlConsole.h"
#include <regex>

CTVSetControlConsole::CTVSetControlConsole(std::istream& inputStream, std::ostream& outputStream, CTVSet& TVSet)
	: m_inputStream(inputStream)
	, m_outputStream(outputStream)
	, m_TVSet(TVSet)

{
}

void CTVSetControlConsole::ProcessSession()
{
	bool isRunning = true;

	while (isRunning)
	{
		const Command command = GetCommand();
		switch (command.name)
		{
		case CommandName::TurnOn:
			m_TVSet.TurnOn();
			break;
		case CommandName::TurnOff:
			m_TVSet.TurnOff();
			break;
		case CommandName::SelectChannel:
			m_TVSet.SetChannel(command.argument);
			break;
		case CommandName::Info:
			PrintTVSetInfo();
			break;
		case CommandName::Exit:
			isRunning = false;
			break;
		case CommandName::Skip:
			break;
		default:
			std::cout << "Unknown command was found\n";
			isRunning = false;
		}
	}
}

bool CTVSetControlConsole::ParseCommand(std::string& inputCommand, Command& command)
{
	std::cmatch result;
	std::regex regular(R"(([\w]+)?[\s]?([\d]+)?)");
	if (!regex_match(inputCommand.c_str(), result, regular))
	{
		return false;
	}

	if (result[1].str().empty())
	{
		command.name = CommandName::Skip;

		return true;
	}

	if (result[2].str().empty())
	{
		command.argument = 0;
	}
	else
	{
		command.argument = std::stoi(result[2].str());
	}

	if (result[1].str() == "Info")
	{
		command.name = CommandName::Info;
	}
	else if (result[1].str() == "TurnOn")
	{
		command.name = CommandName::TurnOn;
	}
	else if (result[1].str() == "TurnOff")
	{
		command.name = CommandName::TurnOff;
	}
	else if (result[1].str() == "SelectChannel")
	{
		command.name = CommandName::SelectChannel;
	}
	else if (result[1].str() == "Exit")
	{
		command.name = CommandName::Exit;
	}
	else
	{
		command.name = CommandName::Skip;
	}

	return true;
}

CTVSetControlConsole::Command CTVSetControlConsole::GetCommand()
{
	Command command;
	std::string inputCommand;
	std::getline(m_inputStream, inputCommand);
	bool isCorrect = ParseCommand(inputCommand, command);
	if (!isCorrect)
	{
		return { CommandName::Skip, 0 };
	}

	return command;
}

void CTVSetControlConsole::PrintTVSetInfo()
{
	m_outputStream << "State: " << (m_TVSet.IsTurnedOn() ? "On" : "Off") << std::endl
				   << "Channel: " << m_TVSet.GetChannel() << std::endl;
}

CTVSetControlConsole::Command 