#pragma once
#include "Calculator.h"

class CalculatorControlConsole
{
public:
	CalculatorControlConsole(std::istream& inputStream, std::ostream& outputStream, Calculator& calculator);
	void ProcessSession();

private:
	enum class CommandName
	{
		DefineVariable,
		AssignVariable,
		DefineFunction,
		PrintIdentifier,
		PrintVariables,
		PrintFunctions,
		ExitCommand,
		SkipCommand,
	};

	struct Command
	{
		CommandName name;
		Calculator::Identifier leftIdentifier;
		Calculator::Identifier rightIdentifier;
		Calculator::Value value;
		Calculator::Expression expression;
	};

	Command GetCommand();
	bool ParseCommand(std::string& inputCommand, Command& command);
	void PrintVariables();
	void PrintFunctions();
	bool PrintIdentifier(const Calculator::Identifier& identifier);
	bool DefineVariable(const Command& command);
	bool AssignVariable(const Command& command);
	bool DefineFunction(const Command& command);
	void SkipCommand();

	bool IsIdentifier(const std::string& string);

	std::istream& m_inputStream;
	std::ostream& m_outputStream;
	Calculator& m_calculator;
};
