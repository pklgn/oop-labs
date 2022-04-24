#include "pch.h"
#include "Calculator.h"
#include "Function.h"

// TODO: перенести из ControlConsole в Calculator IsIdentifier
bool Calculator::DefineVariable(const std::string& identifier)
{
	if (!IsIdentifier(identifier))
	{
		return false;
	}

	if (IsVariableExist(identifier) || IsFunctionExist(identifier))
	{
		return false;
	}

	m_variables[identifier] = NAN;

	return true;
}

bool Calculator::AssignVariable(const std::string& identifier, Value value)
{
	if (!IsIdentifier(identifier))
	{
		return false;
	}

	if (IsFunctionExist(identifier))
	{
		return false;
	}

	m_variables[identifier] = value;

	return true;
}

// TODO: разделить проверку на существование и получение значение
bool Calculator::AssignVariable(const std::string& leftIdentifier, const std::string& rightIdentifier)
{
	if (!(IsIdentifier(leftIdentifier) || IsIdentifier(rightIdentifier)))
	{
		return false;
	}

	if (IsFunctionExist(leftIdentifier))
	{
		return false;
	}

	auto optRightOperand = GetOperandValue(rightIdentifier);

	if (!optRightOperand.has_value())
	{
		return false;
	}

	m_variables[leftIdentifier] = optRightOperand.value();

	return true;
}

bool Calculator::DefineFunction(const std::string& leftIdentifier, const std::string& rightIdentifier)
{
	if (!(IsIdentifier(leftIdentifier) && IsIdentifier(rightIdentifier)))
	{
		return false;
	}

	if (IsVariableExist(leftIdentifier))
	{
		return false;
	}

	m_functions[leftIdentifier].identifier = rightIdentifier;

	return true;
}

bool Calculator::DefineFunction(const std::string& leftIdentifier, const Expression& expression)
{
	if (!IsIdentifier(leftIdentifier))
	{
		return false;
	}

	if (IsVariableExist(leftIdentifier))
	{
		return false;
	}

	if (!(IsIdentifier(expression.operands.first) && IsIdentifier(expression.operands.second)))
	{
		return false;
	}

	if (!(IsVariableExist(expression.operands.first) || IsFunctionExist(expression.operands.first)))
	{
		return false;
	}

	if (!(IsVariableExist(expression.operands.second) || IsFunctionExist(expression.operands.second)))
	{
		return false;
	}

	m_functions[leftIdentifier] = { expression };

	return true;
}

bool Calculator::IsVariableExist(const Identifier& identifier) const
{
	if (m_variables.find(identifier) == m_variables.end())
	{
		return false;
	}

	return true;
}

bool Calculator::IsFunctionExist(const Identifier& identifier) const
{
	if (m_functions.find(identifier) == m_functions.end())
	{
		return false;
	}

	return true;
}

Calculator::Value Calculator::GetVariableValue(const Identifier& identifier) const
{
	auto variableIt = m_variables.find(identifier);

	if (variableIt != m_variables.end())
	{
		return variableIt->second;
	}

	return NAN;
}

Calculator::Value Calculator::GetFunctionValue(const Identifier& identifier) const
{
	// TODO: посчитать значение вместо NAN
	auto functionIt = m_functions.find(identifier);

	if (functionIt != m_functions.end())
	{
		if (functionIt->second.expression.has_value())
		{
			return CalculateExpression(functionIt->second.expression.value());
		}

		return GetOperandValue(functionIt->second.identifier.value()).value();
	}

	return NAN;
}

std::optional<Calculator::Value> Calculator::GetOperandValue(const Identifier& identifier) const
{
	if (!(IsFunctionExist(identifier) || IsVariableExist(identifier)))
	{
		return std::nullopt;
	}

	return IsFunctionExist(identifier) 
		? GetFunctionValue(identifier) 
		: GetVariableValue(identifier);
}

const Calculator::Variables& Calculator::GetVariables() const
{
	return m_variables;
}

const Calculator::Functions& Calculator::GetFunctions() const
{
	return m_functions;
}

Calculator::Value Calculator::CalculateExpression(const Expression& expression) const
{
	auto optLeftOperand = GetOperandValue(expression.operands.first);
	auto optRightOperand = GetOperandValue(expression.operands.second);

	if (isnan(optLeftOperand.value()) || isnan(optRightOperand.value()))
	{
		return NAN;
	}

	switch (expression.operation)
	{
	case Operation::Add:
		return optLeftOperand.value() + optRightOperand.value();
	case Operation::Sub:
		return optLeftOperand.value() - optRightOperand.value();
	case Operation::Mul:
		return optLeftOperand.value() * optRightOperand.value();
	case Operation::Div:
		if (optRightOperand == 0)
		{
			return NAN;
		}
		return optLeftOperand.value() / optRightOperand.value();
	default:
		return NAN;
	}
}

bool Calculator::IsIdentifier(const std::string& string)
{
	std::smatch result;
	std::regex regular(R"(([a-zA-Z_][a-zA-Z0-9_]{0,}))");
	if (!regex_match(string, result, regular))
	{
		return false;
	}

	return true;
}
