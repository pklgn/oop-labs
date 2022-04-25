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

// TODO: убрать command и обрабатывать на месте 
void CalculatorControlConsole::ProcessSession()
{
	bool isRunning = true;
	m_outputStream << std::fixed;
	m_outputStream << std::setprecision(2);

	while (isRunning)
	{
		Command command = GetCommand();
		switch (command.name)
		{
		case CommandName::AssignVariable:
			if (!AssignVariable(command))
			{
				m_outputStream << "Can't assign variable\n";
			}
			break;
		case CommandName::DefineFunction:
			if (!DefineFunction(command))
			{
				m_outputStream << "Can't define function\n";
			}
			break;
		case CommandName::DefineVariable:
			if (!DefineVariable(command))
			{
				m_outputStream << "Can't define variable\n";
			}
			break;
		case CommandName::PrintIdentifier:
			if (!PrintIdentifier(command))
			{
				m_outputStream << "Can't print value of the specified identifier\n";
			}
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
			m_outputStream << "Internal error was found\n";
			isRunning = false;
		}
	}
}

CalculatorControlConsole::Command CalculatorControlConsole::GetCommand() const
{
	Command command;
	std::getline(m_inputStream, command.string);
	bool isCorrect = ParseCommand(command.string, command);
	if (!isCorrect)
	{
		return { CommandName::SkipCommand };
	}

	return command;
}

bool CalculatorControlConsole::ParseCommand(std::string& inputCommand, Command& command) const
{
	std::string commandName;

	if (!ReadIdentifier(inputCommand, commandName))
	{
		return false;
	}

	if (commandName == "var")
	{
		command.name = CommandName::DefineVariable;
	}
	else if (commandName == "let")
	{
		command.name = CommandName::AssignVariable;
	}
	else if (commandName == "fn")
	{
		command.name = CommandName::DefineFunction;
	}
	else if (commandName == "print")
	{
		command.name = CommandName::PrintIdentifier;
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

		m_outputStream << m_calculator.GetOperandValue(function.first).value() << std::endl;
	}
}

bool CalculatorControlConsole::PrintIdentifier(Command& command)
{
	std::string identifier;
	if (!ReadIdentifier(command.string, identifier))
	{
		return false;
	}

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

bool CalculatorControlConsole::DefineVariable(Command& command)
{
	// TODO: получать операнды здесь
	std::string identifier;
	if (!ReadIdentifier(command.string, identifier))
	{
		return false;
	}
	return m_calculator.DefineVariable(identifier);
}

bool CalculatorControlConsole::AssignVariable(Command& command)
{
	std::string leftIdentifier;
	if (!ReadIdentifier(command.string, leftIdentifier, " ="))
	{
		return false;
	}
	TrimLeft(command.string, "=");

	std::string rightIdentifier;

	if (!ReadIdentifier(command.string, rightIdentifier))
	{
		return false;
	}

	if (m_calculator.IsIdentifier(rightIdentifier))
	{
		return m_calculator.AssignVariable(leftIdentifier, rightIdentifier);
	}

	Calculator::Value value;
	try
	{
		value = std::stod(rightIdentifier);
	}
	catch (...)
	{
		return false;
	}

	return m_calculator.AssignVariable(leftIdentifier, value);
}

bool CalculatorControlConsole::DefineFunction(Command& command)
{
	std::string leftIdentifier;
	if (!ReadIdentifier(command.string, leftIdentifier, " ="))
	{
		return false;
	}
	TrimLeft(command.string, "=");

	std::string operand;
	if (!ReadIdentifier(command.string, operand, "+-*/"))
	{
		return false;
	}

	size_t operationChPos = command.string.find_first_of("+-*/");
	std::string rightIdentifier;
	if (operationChPos == std::string::npos)
	{
		return m_calculator.DefineFunction(leftIdentifier, operand);
	}

	char operationCh = command.string[operationChPos];
	command.string.erase(0, operationChPos + 1);

	Calculator::Expression expression;
	expression.operands.first = operand;

	auto operation = ParseOperation(operationCh);
	if (!operation.has_value())
	{
		return false;
	}
	expression.operation = operation.value();

	if (!ReadIdentifier(command.string, expression.operands.second))
	{
		return false;
	}

	return m_calculator.DefineFunction(leftIdentifier, expression);
}

void CalculatorControlConsole::SkipCommand()
{
	m_outputStream << "Cannot execute this command\n";
}

std::optional<Calculator::Operation> CalculatorControlConsole::ParseOperation(char operationCh) const
{
	switch (operationCh)
	{
	case '+':
		return Calculator::Operation::Add;
	case '-':
		return Calculator::Operation::Sub;
	case '*':
		return Calculator::Operation::Mul;
	case '/':
		return Calculator::Operation::Div;
	default:
		return std::nullopt;
	}
}

bool CalculatorControlConsole::ReadIdentifier(std::string& sourceString, std::string& result, 
	const std::string& delimeters) const
{
	size_t beginPos = sourceString.find_first_not_of(delimeters);
	if (beginPos == std::string::npos)
	{
		return false;
	}
	std::string rawResult = sourceString.substr(beginPos);
	sourceString.erase(0, beginPos);
	size_t endPos = sourceString.find_first_of(delimeters);
	result = sourceString.substr(0, endPos);
	sourceString.erase(0, endPos);

	if (result.size() == 0)
	{
		return false;
	}

	return true;
}

void CalculatorControlConsole::TrimLeft(std::string& string, const std::string& delimeters) const
{
	size_t beginPos = string.find_first_not_of(delimeters);
	string.erase(0, beginPos);
}
