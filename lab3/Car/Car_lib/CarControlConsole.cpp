#include "pch.h"
#include "CarControlConsole.h"
#include <regex>

// TODO: при вводе неизвестных команд выдывать сообщение
// TODO: если команду выполнить нельзя - выдавать сообщение
// TODO: исправить переключение 2 передачи при движении задом: написать тест для этой ситуации и исправить программу
// TODO: исправить SetGear 2 -> 0 (см скриншот)
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
			m_Car.TurnOnEngine();
			break;
		case CommandName::EngineOff:
			m_Car.TurnOffEngine();
			break;
		case CommandName::SetGear:
			m_Car.SetGear(command.argument);
			break;
		case CommandName::SetSpeed:
			m_Car.SetSpeed(command.argument);
			break;
		case CommandName::Info:
			PrintCarInfo();
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

bool CarControlConsole::ParseCommand(std::string& inputCommand, Command& command)
{
	std::cmatch result;
	std::regex regular(R"(([\w]+)?[\s]?(-?[\d]{0,3})?)");
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
	else
	{
		command.name = CommandName::Skip;
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
		return { CommandName::Skip, 0 };
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

void CarControlConsole::PrintCarInfo()
{
	Car::Direction direction = m_Car.GetDirection();
	std::string directionStr = GetDirectionString(direction);
	m_outputStream << "Engine: " << (m_Car.IsTurnedOn() ? "On" : "Off") << std::endl
				   << "Direction: " << directionStr << std::endl
				   << "Speed: " << (m_Car.GetSpeed()) << std::endl
				   << "Gear: " << m_Car.GetGear() << std::endl;
}