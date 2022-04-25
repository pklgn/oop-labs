#pragma once

class Function
{
public:
	enum class Operation
	{
		Add,
		Sub,
		Mul,
		Div,
	};

	typedef std::optional<Calculator::Value> CachedValue;
	typedef std::pair<Calculator::Identifier, Calculator::Identifier> Operands;

	struct Expression
	{
		Operands operands;
		Operation operation;
	};

	Function(const CachedValue& value): m_value(value)
	{
	}

	Function(const Expression* expressionPtr)
		: m_expressionPtr(expressionPtr)
	{
	}

private:
	Calculator::Value CalculateExpression(const Expression* expression) const;

	const Expression* m_expressionPtr;
	mutable std::optional<Calculator::Value> m_value;
};
