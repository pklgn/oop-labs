#include "pch.h"
#include "Calculator.h"

// TODO: isidentifier
bool Calculator::DefineVariable(const Identifier& identifier)
{
	if (GetOperandValue(identifier).has_value())
	{
		return false;
	}
	m_variables[identifier] = NAN;

	return true;
}

bool Calculator::AssignVariable(const Identifier& identifier, Value value)
{
	if (GetFunctionValue(identifier).has_value())
	{
		return false;
	}

	m_variables[identifier] =  value;

	return true;
}
// TODO: разделить проверку на существование и получение значение
bool Calculator::AssignVariable(const Identifier& leftIdentifier, const Identifier& rightIdentifier)
{
	if (GetFunctionValue(leftIdentifier).has_value())
	{
		return false;
	}

	std::optional<Value> rightOperand = GetOperandValue(rightIdentifier);
	if (!rightOperand.has_value())
	{
		return false;
	}

	m_variables[leftIdentifier] = rightOperand.value();

	return true;
}

bool Calculator::DefineFunction(const Identifier& leftIdentifier, const Identifier& rightIdentifier)
{
	if (GetVariableValue(leftIdentifier).has_value())
	{
		return false;
	}

	auto rightOperand = GetOperandValue(rightIdentifier);
	if (!rightOperand.has_value())
	{
		return false;
	}

	m_functions[leftIdentifier] = rightOperand.value();

	return true;
}

bool Calculator::DefineFunction(const Identifier& leftIdentifier, const Expression& expression)
{
	if (GetVariableValue(leftIdentifier).has_value())
	{
		return false;
	}

	Value expressionValue = CalculateExpression(expression);

	m_functions[leftIdentifier] = expressionValue;

	return true;
}

std::optional<Calculator::Value> Calculator::GetVariableValue(const Identifier& identifier) const
{
	auto variableIt = m_variables.find(identifier);

	if (variableIt != m_variables.end())
	{
		return variableIt->second;
	}

	return std::nullopt;
}

std::optional<Calculator::Value> Calculator::GetFunctionValue(const Identifier& identifier) const
{
	// TODO: посчитать значение вместо NAN
	auto functionIt = m_functions.find(identifier);

	if (functionIt != m_functions.end())
	{
		return functionIt->second.value_or(NAN);
	}

	return std::nullopt;
}

std::optional<Calculator::Value> Calculator::GetOperandValue(const Identifier& identifier) const
{
	std::optional<Value> functionValue = GetFunctionValue(identifier);
	std::optional<Value> variableValue = GetVariableValue(identifier);
	return variableValue.has_value()
		? variableValue
		: functionValue;
}

const Calculator::Variables& Calculator::GetVariables() const
{
	return m_variables;
}

const Calculator::Functions& Calculator::GetFunctions() const
{
	return m_functions;
}

Calculator::Value Calculator::CalculateExpression(const Expression& expression)
{
	auto leftOperand = GetOperandValue(expression.operands.first);
	auto rightOperand = GetOperandValue(expression.operands.second);
	if (!(leftOperand.has_value() && rightOperand.has_value()))
	{
		return NAN;
	}

	switch (expression.operation)
	{
	case Operation::Add:
		return leftOperand.value() + rightOperand.value();
	case Operation::Sub:
		return leftOperand.value() - rightOperand.value();
	case Operation::Mul:
		return leftOperand.value() * rightOperand.value();
	case Operation::Div:
		if (rightOperand.value() == 0)
		{
			return NAN;
		}
		return leftOperand.value() / rightOperand.value();
	default:
		return NAN;
	}
}
