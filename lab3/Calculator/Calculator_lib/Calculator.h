#pragma once
#include "pch.h"

class Calculator
{
public:
	// TODO: перенсти в Private
	typedef double Value;
	typedef std::string Identifier;

	enum class Operation
	{
		Add,
		Sub,
		Mul,
		Div,
	};
	typedef std::pair<Identifier, Identifier> Operands;
	struct Expression
	{
		Operands operands;
		Operation operation;
	};

	struct Function
	{
		std::optional<Expression> expression;
		std::optional<Identifier> identifier;
	};

	typedef std::map<Identifier, Function> Functions;
	typedef std::map<Identifier, Value> Variables;

	bool DefineVariable(const std::string& identifier);
	bool AssignVariable(const std::string& identifier, Value value = NAN);
	bool AssignVariable(const std::string& leftIdentifier, const std::string& rightIdentifier);

	bool DefineFunction(const std::string& leftIdentifier, const std::string& rightIdentifier);
	bool DefineFunction(const std::string& leftIdentifier, const Expression& expression);

	const Variables& GetVariables() const;
	const Functions& GetFunctions() const;
	std::optional<Value> GetOperandValue(const Identifier& identifier) const;
	bool IsIdentifier(const std::string& string);

private:
	bool IsVariableExist(const Identifier& identifier) const;
	bool IsFunctionExist(const Identifier& identifier) const;
	Value GetVariableValue(const Identifier& identifier) const;
	Value GetFunctionValue(const Identifier& identifier) const;
	Value CalculateExpression(const Expression& expression) const;

	Functions m_functions;
	Variables m_variables;
	std::map<Identifier, std::set<Identifier>> m_state;
};
