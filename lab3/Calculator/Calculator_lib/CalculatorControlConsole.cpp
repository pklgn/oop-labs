#include "pch.h"
#include "CalculatorControlConsole.h"

const std::string STRING_NAN = "NAN";

CalculatorControlConsole::CalculatorControlConsole(std::istream& inputStream, 
	std::ostream& outputStream, Calculator& calculator)
	: m_inputStream(inputStream)
	, m_outputStream(outputStream)
	, m_calculator(calculator)
{
}

void CalculatorControlConsole::ProcessSession()
{
	bool isRunning = true;
	m_outputStream << std::fixed;
	m_outputStream << std::setprecision(2);

	while (isRunning)
	{
		const Command command = GetCommand();
		switch (command.name)
		{
		case CommandName::AssignVariable:
			AssignVariable(command);
			break;
		case CommandName::DefineFunction:
			DefineFunction(command);
			break;
		case CommandName::DefineVariable:
			DefineVariable(command);
			break;
		case CommandName::PrintIdentifier:
			PrintIdentifier(command.leftIdentifier);
			break;
		case CommandName::PrintFunctions:
			PrintFunctions();
			break;
		case CommandName::PrintVariables:
			PrintVariables();
			break;
		case CommandName::ExitCommand:
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

CalculatorControlConsole::Command CalculatorControlConsole::GetCommand()
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

bool CalculatorControlConsole::ParseCommand(std::string& inputCommand, Command& command)
{
	std::smatch result;
	std::stringstream commandStream(inputCommand);
	
	std::string commandName;
	commandStream >> commandName;

	if (commandName == "var")
	{
		command.name = CommandName::DefineVariable;
		commandStream >> command.leftIdentifier;
		if (!IsIdentifier(command.leftIdentifier))
		{
			return false;
		}
	}
	else if (commandName == "let")
	{
		command.name = CommandName::AssignVariable;
		commandStream >> command.leftIdentifier;
		if (!IsIdentifier(command.leftIdentifier))
		{
			return false;
		}
		char delimeter;
		commandStream >> delimeter;
		std::string operand;
		commandStream >> operand;
		if (IsIdentifier(operand))
		{
			command.rightIdentifier = operand;
		}
		else
		{
			command.value = std::stoi(operand);
		}
	}
	else if (commandName == "fn")
	{
		command.name = CommandName::DefineFunction;
		commandStream >> command.leftIdentifier;
		if (!IsIdentifier(command.leftIdentifier))
		{
			return false;
		}
		char delimeter;
		commandStream >> delimeter;
		std::string operand;
		commandStream >> operand;
		if (commandStream.eof())
		{
			command.rightIdentifier = operand;

			return true;
		}
		Calculator::Expression expression;
		expression.operands.first = operand;
		char operation;
		commandStream >> operation;
		switch (operation)
		{
		case '+':
			expression.operation = Calculator::Operation::Add;
			break;
		case '-':
			expression.operation = Calculator::Operation::Sub;
			break;
		case '*':
			expression.operation = Calculator::Operation::Mul;
			break;
		case '/':
			expression.operation = Calculator::Operation::Div;
			break;
		default:
			return false;
		}
		commandStream >> expression.operands.second;

		command.expression = expression;
	}
	else if (commandName == "print")
	{
		command.name = CommandName::PrintIdentifier;
		commandStream >> command.leftIdentifier;
		if (!IsIdentifier(command.leftIdentifier))
		{
			return false;
		}
	}
	else if (commandName == "printvars")
	{
		command.name = CommandName::PrintVariables;
	}
	else if (commandName == "printfns")
	{
		command.name = CommandName::PrintFunctions;
	}
	else if (commandName == "exit")
	{
		command.name = CommandName::ExitCommand;
	}	
	else
	{
		command.name = CommandName::SkipCommand;
	}

	return true;
}

void CalculatorControlConsole::PrintVariables()
{
	for (auto& variable : m_calculator.GetVariables())
	{
		m_outputStream << variable.first << ": ";
		if (isnan(variable.second))
		{
			m_outputStream << STRING_NAN;
		}
		else
		{
			m_outputStream << variable.second;
		}
		m_outputStream << std::endl;
	}
}

void CalculatorControlConsole::PrintFunctions()
{
	for (auto& function : m_calculator.GetFunctions())
	{
		m_outputStream << function.first << ": ";

		if (isnan(function.second.value()))
		{
			m_outputStream << STRING_NAN;
		}
		else
		{
			m_outputStream << function.second.value();
		}
		m_outputStream << std::endl;
	}
}

bool CalculatorControlConsole::PrintIdentifier(const Calculator::Identifier& identifier)
{
	auto operand = m_calculator.GetOperandValue(identifier);
	if (!operand.has_value())
	{
		m_outputStream << "Cannot find such identifier\n";

		return false;
	}
	m_outputStream << identifier << ": ";
	if (isnan(operand.value()))
	{
		m_outputStream << STRING_NAN;
	}
	else
	{
		m_outputStream << operand.value();
	}
	m_outputStream << std::endl;

	return true;
}

bool CalculatorControlConsole::DefineVariable(const Command& command)
{
	return m_calculator.DefineVariable(command.leftIdentifier);
}

bool CalculatorControlConsole::AssignVariable(const Command& command)
{
	if (IsIdentifier(command.rightIdentifier))
	{
		return m_calculator.AssignVariable(command.leftIdentifier, command.rightIdentifier);
	}
	
	return m_calculator.AssignVariable(command.leftIdentifier, command.value);
}

bool CalculatorControlConsole::DefineFunction(const Command& command)
{
	if (IsIdentifier(command.rightIdentifier))
	{
		return m_calculator.DefineFunction(command.leftIdentifier, command.rightIdentifier);
	}

	return m_calculator.DefineFunction(command.leftIdentifier, command.expression);
}

void CalculatorControlConsole::SkipCommand()
{
	m_outputStream << "Cannot execute this command. "
					  "Use Help to see all commands\n";
}

bool CalculatorControlConsole::IsIdentifier(const std::string& string)
{
	std::smatch result;
	std::regex regular(R"(([a-zA-Z_][\w_]{0,}))");
	if (!regex_match(string, result, regular))
	{
		return false;
	}

	return true;
}
