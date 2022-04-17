#include "pch.h"
#include "Calculator.h"

bool Calculator::AddVariable(const Identifier& identifier)
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
