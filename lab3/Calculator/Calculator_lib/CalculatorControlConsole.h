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
		std::string string;
	};

	Command GetCommand() const;
	bool ParseCommand(std::string& inputCommand, Command& command) const;
	void PrintVariables();
	void PrintFunctions();
	bool PrintIdentifier(Command& command);
	bool DefineVariable(Command& command);
	bool AssignVariable(Command& command);
	bool DefineFunction(Command& command);
	void SkipCommand();
	std::optional<Calculator::Operation> ParseOperation(char operationCh) const;
	bool ReadIdentifier(std::string& sourceString, std::string& result, const std::string& delimeters = " \n") const;
	void TrimLeft(std::string& string, const std::string& delimeters) const;

	std::istream& m_inputStream;
	std::ostream& m_outputStream;
	Calculator& m_calculator;
};
