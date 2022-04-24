#pragma once
#include "Calculator.h"

class CalculatorControlConsole
{
public:
	// TODO: center | controller
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
	// TODO: 

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
	std::optional<Calculator::Operation> ParseOperation(char operationCh);
	bool ReadWord(std::string& sourceString, std::string& result, const std::string& delimeters = " \n");
	void TrimLeft(std::string& string, const std::string& delimeters) const;

	std::istream& m_inputStream;
	std::ostream& m_outputStream;
	Calculator& m_calculator;
};
