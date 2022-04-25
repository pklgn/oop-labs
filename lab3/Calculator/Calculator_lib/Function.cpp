#include "pch.h"
#include "Function.h"

Calculator::Value Function::CalculateExpression(const Function::Expression* expression) const
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