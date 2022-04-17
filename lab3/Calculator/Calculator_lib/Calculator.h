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
	typedef double Value;
	typedef std::optional<Value> CachedValue;
	typedef std::string Identifier;
	typedef std::map<Identifier, CachedValue> Functions;
	typedef std::map<Identifier, Value> Variables;
	typedef std::pair<Identifier, Identifier> Operands;
	
	struct Expression
	{
		Operands operands;
		Operation operation;
	};

	bool DefineVariable(const Identifier& identifier);
	bool AssignVariable(const Identifier& identifier, Value value = NAN);
	bool AssignVariable(const Identifier& leftIdentifier, const Identifier& rightIdentifier);

	bool DefineFunction(const Identifier& leftIdentifier, const Identifier& rightIdentifier);
	bool DefineFunction(const Identifier& leftIdentifier, const Expression& expression);

	std::optional<Value> GetOperandValue(const Identifier& identifier) const;
	const Variables& GetVariables() const;
	const Functions& GetFunctions() const;

private:
	std::optional<Value> GetVariableValue(const Identifier& identifier) const;
	std::optional<Value> GetFunctionValue(const Identifier& identifier) const;
	
	Value CalculateExpression(const Expression& expression);

	Functions m_functions;
	Variables m_variables;
};
