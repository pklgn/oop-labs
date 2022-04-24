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
			// TODO: добавить отчет об ошибке
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

// TODO: const params
bool CalculatorControlConsole::ParseCommand(std::string& inputCommand, Command& command)
{
	std::string commandName;
	/*size_t delimeterPos = inputCommand.find_first_of(" \n");

	commandName = inputCommand.substr(0, delimeterPos);
	inputCommand.erase(0, delimeterPos);*/
	ReadWord(inputCommand, commandName);

	if (commandName == "var")
	{
		command.name = CommandName::DefineVariable;
		if (!ReadWord(inputCommand, command.leftIdentifier))
		{
			return false;
		}
	}
	else if (commandName == "let")
	{
		command.name = CommandName::AssignVariable;
		ReadWord(inputCommand, command.leftIdentifier, " =");
		TrimLeft(inputCommand, "=");

		std::string operand;
		ReadWord(inputCommand, operand);
		if (m_calculator.IsIdentifier(operand))
		{
			command.rightIdentifier = operand;

			return true;
		}
		try
		{
			command.value = std::stod(operand);
		}
		catch (...)
		{
			return false;
		}
	}
	else if (commandName == "fn")
	{
		command.name = CommandName::DefineFunction;
		ReadWord(inputCommand, command.leftIdentifier, " =");
		TrimLeft(inputCommand, "=");

		std::string operand;
		ReadWord(inputCommand, operand, "+-*/");

		size_t operationChPos = inputCommand.find_first_of("+-*/");
		if (operationChPos == std::string::npos)
		{
			command.rightIdentifier = operand;

			return true;
		}
		char operationCh = inputCommand[operationChPos];
		inputCommand.erase(0, operationChPos + 1);

		Calculator::Expression expression;
		expression.operands.first = operand;
		
		auto operation = ParseOperation(operationCh);
		if (!operation.has_value())
		{
			return false;
		}
		expression.operation = operation.value();
		ReadWord(inputCommand, expression.operands.second);

		command.expression = expression;
	}
	else if (commandName == "print")
	{
		command.name = CommandName::PrintIdentifier;
		ReadWord(inputCommand, command.leftIdentifier);
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
// TODO: print operands
void CalculatorControlConsole::PrintFunctions()
{
	for (auto& function : m_calculator.GetFunctions())
	{
		m_outputStream << function.first << ": ";

		m_outputStream << m_calculator.GetOperandValue(function.first).value() << std::endl;
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
	// TODO: получать операнды здесь
	return m_calculator.DefineVariable(command.leftIdentifier);
}

bool CalculatorControlConsole::AssignVariable(const Command& command)
{
	if (m_calculator.IsIdentifier(command.rightIdentifier))
	{
		return m_calculator.AssignVariable(command.leftIdentifier, command.rightIdentifier);
	}
	
	return m_calculator.AssignVariable(command.leftIdentifier, command.value);
}

bool CalculatorControlConsole::DefineFunction(const Command& command)
{
	if (m_calculator.IsIdentifier(command.rightIdentifier))
	{
		return m_calculator.DefineFunction(command.leftIdentifier, command.rightIdentifier);
	}

	return m_calculator.DefineFunction(command.leftIdentifier, command.expression);
}

void CalculatorControlConsole::SkipCommand()
{
	m_outputStream << "Cannot execute this command.\n";
}

std::optional<Calculator::Operation> CalculatorControlConsole::ParseOperation(char operationCh)
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

bool CalculatorControlConsole::ReadWord(std::string& sourceString, std::string& result, 
	const std::string& delimeters)
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
	
	//if (endPos != std::string::npos)
	//{
	//	endPos++;
	//}
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
