#include "pch.h"
#include "CarControlConsole.h"
#include <regex>

// TODO: при вводе неизвестных команд выдывать сообщение
// TODO: если команду выполнить нельзя - выдавать сообщение
// TODO: исправить переключение 2 передачи при движении задом: написать тест для этой ситуации и исправить программу
// TODO: исправить SetGear 2 -> 0
CarControlConsole::CarControlConsole(std::istream& inputStream, std::ostream& outputStream, Car& car)
	: m_inputStream(inputStream)
	, m_outputStream(outputStream)
	, m_Car(car)
{
}

void CarControlConsole::ProcessSession()
{
	bool isRunning = true;

	while (isRunning)
	{
		const Command command = GetCommand();
		switch (command.name)
		{
		case CommandName::EngineOn:
			EngineOn();
			break;
		case CommandName::EngineOff:
			EngineOff();
			break;
		case CommandName::SetGear:
			SetGear(command.argument);
			break;
		case CommandName::SetSpeed:
			SetSpeed(command.argument);
			break;
		case CommandName::Info:
			PrintInfo();
			break;		
		case CommandName::Help:
			PrintHelp();
			break;
		case CommandName::Exit:
			isRunning = false;
			break;
		case CommandName::SkipCommand:
			SkipCommand();
			break;
		default:
			isRunning = false;
		}
	}
}

bool CarControlConsole::ParseCommand(std::string& inputCommand, Command& command)
{
	std::smatch result;
	std::regex regular(R"(\s{0,}([\w]+)?[\s]?(-?[\d]{0,3})?\s{0,})");
	if (!regex_match(inputCommand, result, regular))
	{
		return false;
	}

	if (result[1].str().empty())
	{
		command.name = CommandName::SkipCommand;

		return true;
	}

	if (result[1].str() == "Info")
	{
		command.name = CommandName::Info;
	}
	else if (result[1].str() == "EngineOn")
	{
		command.name = CommandName::EngineOn;
	}
	else if (result[1].str() == "EngineOff")
	{
		command.name = CommandName::EngineOff;
	}
	else if (result[1].str() == "SetGear")
	{
		command.name = CommandName::SetGear;
	}
	else if (result[1].str() == "SetSpeed")
	{
		command.name = CommandName::SetSpeed;
	}
	else if (result[1].str() == "Exit")
	{
		command.name = CommandName::Exit;
	}	
	else if (result[1].str() == "Help")
	{
		command.name = CommandName::Help;
	}
	else
	{
		command.name = CommandName::SkipCommand;
	}

	if (result[2].str().empty())
	{
		if (command.name == CommandName::SetGear || command.name == CommandName::SetSpeed)
		{
			return false;
		}
	}
	else
	{
		command.argument = std::stoi(result[2].str());
	}

	return true;
}

CarControlConsole::Command CarControlConsole::GetCommand()
{
	Command command;
	std::string inputCommand;
	std::getline(m_inputStream, inputCommand);
	bool isCorrect = ParseCommand(inputCommand, command);
	if (!isCorrect)
	{
		return { CommandName::SkipCommand };
	}

	return command;
}

std::string GetDirectionString(Car::Direction& direction)
{
	switch (direction)
	{
	case Car::Direction::Forwards:
		return "Forwards";
	case Car::Direction::InPlace:
		return "In place";
	case Car::Direction::Backwards:
		return "Backwards";
	default:
		return "";
	}
}

void CarControlConsole::PrintInfo()
{
	Car::Direction direction = m_Car.GetDirection();
	std::string directionStr = GetDirectionString(direction);
	m_outputStream << "Engine:\t\t " << (m_Car.IsTurnedOn() ? "On" : "Off") << std::endl
				   << "Direction:\t " << directionStr << std::endl
				   << "Speed:\t\t " << (m_Car.GetSpeed()) << std::endl
				   << "Gear:\t\t " << m_Car.GetGear() << std::endl;
}

void CarControlConsole::PrintHelp()
{
	m_outputStream << "Info:\t\t prints vehicle engine status, driving direction, speed and gear\n"
					  "EngineOn:\t turns the engine on\n"
					  "EngineOff:\t turns the engine off\n"
					  "SetGear:\t switch gear with specifeid number\n"
					  "SetSpeed:\t set specified speed value\n"
					  "Exit:\t\t finish current console session\n";
}

void CarControlConsole::SkipCommand()
{
	m_outputStream << "Cannot execute this command. "
					  "Use Help to see all commands\n";
}

void CarControlConsole::EngineOn()
{
	if (!m_Car.TurnOnEngine())
	{
		m_outputStream << "Cannot turn the engine on\n";
	}

	return;
}

void CarControlConsole::EngineOff()
{
	if (!m_Car.TurnOffEngine())
	{
		m_outputStream << "Cannot turn the engine off\n";
	}

	return;
}

void CarControlConsole::SetGear(int gear)
{
	if (!m_Car.SetGear(gear))
	{
		m_outputStream << "Cannot switch gear to " << gear << std::endl;
	}

	return;
}

void CarControlConsole::SetSpeed(int speed)
{
	if (!m_Car.SetSpeed(speed))
	{
		m_outputStream << "Cannot set speed to " << speed << std::endl;
	}

	return;
}