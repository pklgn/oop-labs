#pragma once
#include "pch.h"

class Calculator
{
public:
	enum class Operation
	{
		Add,
		Sub,
		Mul,
		Div,
	};
	typedef std::optional<double> Value;
	typedef std::string Identifier;
	typedef std::map<Identifier, Value> Functions;
	typedef std::map<Identifier, Value> Variables;
	typedef std::pair<Identifier, Identifier> Operands;
	
	struct Expression
	{
		Operands operands;
		Operation operation;
	};

	bool AddVariable(Identifier& identifier, Value value = NAN);
	bool AddVariable(Identifier& leftIdentifier, Identifier& rightIdentifier);

	bool AddFunction(Identifier& leftIdentifier, Identifier& rightIdentifier);
	bool AddFunction(Identifier& leftIdentifier, Expression& expression);

	bool PrintIdentifier(Identifier& identifier);
	void PrintVariables();
	void PrintFunctions();

private:
	Functions m_functions;
	Variables m_variables;
};
