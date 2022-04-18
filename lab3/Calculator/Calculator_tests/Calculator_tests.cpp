#define CATCH_CONFIG_MAIN
#include "../Calculator_lib/Calculator.h"
#include "../Calculator_lib/CalculatorControlConsole.h"
#include "../../../catch2/catch.hpp"
#include <sstream>

SCENARIO("Calculator class works properly")
{
	Calculator calculator;
	WHEN("Calculator has been  just created")
	{
		THEN("Functions and variables size will be equal to zero")
		{
			REQUIRE(calculator.GetFunctions().size() == 0);
			REQUIRE(calculator.GetVariables().size() == 0);
		}
	}
	WHEN("Try to declare variable")
	{
		Calculator::Identifier identifier = "identifier";
		calculator.DefineVariable(identifier);
		THEN("Variables map size will be equal to 1 and value will be NAN")
		{
			REQUIRE(calculator.GetVariables().size() == 1);
			REQUIRE(isnan(calculator.GetOperandValue(identifier).value()));
		}
	}
	WHEN("Try to declare a new variable with the same id")
	{
		Calculator::Identifier identifier = "identifier";
		calculator.DefineVariable(identifier);
		THEN("Variable amount will not change")
		{
			REQUIRE(!calculator.DefineVariable(identifier));
			REQUIRE(calculator.GetVariables().size() == 1);
		}
	}
	WHEN("Try to declare a new function with the same id")
	{
		Calculator::Identifier identifier = "identifier";
		calculator.DefineVariable(identifier);
		THEN("Functions amount will not change")
		{
			REQUIRE(!calculator.DefineFunction(identifier, identifier));
			REQUIRE(calculator.GetVariables().size() == 1);
			REQUIRE(calculator.GetFunctions().size() == 0);
		}
	}
	WHEN("Try to declare a new function with the different id")
	{
		Calculator::Identifier identifier = "identifier";
		calculator.DefineVariable(identifier);
		THEN("There will be 2 operands")
		{
			REQUIRE(calculator.DefineFunction("fnIdentifier", identifier));
			REQUIRE(calculator.GetVariables().size() == 1);
			REQUIRE(calculator.GetFunctions().size() == 1);
		}
	}
	WHEN("Try to declare several variables")
	{
		Calculator::Identifier identifier1 = "varIdentifier1";
		Calculator::Identifier identifier2 = "varIdentifier2";
		calculator.DefineVariable(identifier1);
		calculator.DefineVariable(identifier2);
		THEN("There will be 2 operands")
		{
			REQUIRE(calculator.GetVariables().size() == 2);
		}
	}
	WHEN("Try to declare several variables and assign a value to them")
	{
		Calculator::Identifier identifier1 = "varIdentifier1";
		Calculator::Identifier identifier2 = "varIdentifier2";
		calculator.AssignVariable(identifier1, 1);
		calculator.AssignVariable(identifier2, 2);
		THEN("There will be 2 operands")
		{
			REQUIRE(calculator.GetVariables().size() == 2);
			REQUIRE(calculator.GetOperandValue(identifier1).value() == 1);
			REQUIRE(calculator.GetOperandValue(identifier2).value() == 2);
		}
	}
	WHEN("Try to declare several variables with a value and create function with one of them")
	{
		Calculator::Identifier identifier1 = "varIdentifier1";
		Calculator::Identifier identifier2 = "varIdentifier2";
		calculator.AssignVariable(identifier1, 1);
		calculator.AssignVariable(identifier2, 2);
		THEN("There will be 2 operands")
		{
			Calculator::Identifier fnIdentifier = "fnIdentifier";
			REQUIRE(calculator.DefineFunction(fnIdentifier, identifier1));
			REQUIRE(calculator.GetOperandValue(fnIdentifier).value() == 1);
		}
	}
	WHEN("Try to declare several variables with a value and create function with them with each operation")
	{
		Calculator::Identifier identifier1 = "varIdentifier1";
		Calculator::Identifier identifier2 = "varIdentifier2";
		calculator.AssignVariable(identifier1, 1);
		calculator.AssignVariable(identifier2, 2);
		THEN("There will be 2 operands and their sum")
		{
			Calculator::Identifier fnIdentifier = "fnIdentifierAdd";
			Calculator::Expression expression;
			expression.operation = Calculator::Operation::Add;
			expression.operands = { identifier1, identifier2 };
			REQUIRE(calculator.DefineFunction(fnIdentifier, expression));
			REQUIRE(calculator.GetOperandValue(fnIdentifier).value() == 3);
		}
		THEN("There will be 2 operands and their sub")
		{
			Calculator::Identifier fnIdentifier = "fnIdentifierAdd";
			Calculator::Expression expression;
			expression.operation = Calculator::Operation::Sub;
			expression.operands = { identifier1, identifier2 };
			REQUIRE(calculator.DefineFunction(fnIdentifier, expression));
			REQUIRE(calculator.GetOperandValue(fnIdentifier).value() == -1);
		}
		THEN("There will be 2 operands and their mul")
		{
			Calculator::Identifier fnIdentifier = "fnIdentifierAdd";
			Calculator::Expression expression;
			expression.operation = Calculator::Operation::Mul;
			expression.operands = { identifier1, identifier2 };
			REQUIRE(calculator.DefineFunction(fnIdentifier, expression));
			REQUIRE(calculator.GetOperandValue(fnIdentifier).value() == 2);
		}
		THEN("There will be 2 operands and their div")
		{
			Calculator::Identifier fnIdentifier = "fnIdentifierAdd";
			Calculator::Expression expression;
			expression.operation = Calculator::Operation::Div;
			expression.operands = { identifier1, identifier2 };
			REQUIRE(calculator.DefineFunction(fnIdentifier, expression));
			REQUIRE(calculator.GetOperandValue(fnIdentifier).value() == 0.5);
		}
	}
	WHEN("Try to define a function with the id that already exists")
	{
		Calculator::Identifier identifier1 = "varIdentifier1";
		calculator.AssignVariable(identifier1, 1);

		THEN("Number of functions will not change")
		{
			Calculator::Identifier fnIdentifier = "fnIdentifier";
			REQUIRE(calculator.DefineFunction(fnIdentifier, identifier1));
			REQUIRE(calculator.GetFunctions().size() == 1);
			REQUIRE(!calculator.DefineFunction(identifier1, identifier1));
			REQUIRE(calculator.GetFunctions().size() == 1);
		}
	}
	WHEN("Change variable value and function will change")
	{
		Calculator::Identifier identifier1 = "varIdentifier1";
		calculator.AssignVariable(identifier1, 1);
		THEN("Function value will change")
		{
			Calculator::Identifier fnIdentifier = "fnIdentifierAdd";
			Calculator::Expression expression;
			expression.operation = Calculator::Operation::Add;
			expression.operands = { identifier1, identifier1 };
			REQUIRE(calculator.DefineFunction(fnIdentifier, expression));
			REQUIRE(calculator.GetOperandValue(fnIdentifier).value() == 2);
			REQUIRE(calculator.AssignVariable(identifier1, 2));
			REQUIRE(calculator.GetOperandValue(fnIdentifier).value() == 4);
		}
	}
}

SCENARIO("CalculatorControlConsole works properly")
{
	Calculator calculator;
	std::istringstream inputStream;
	std::ostringstream outputStream;
	CalculatorControlConsole console(inputStream, outputStream, calculator);

	WHEN("Define variable with NAN")
	{
		inputStream.str("var id1\nprint id1\nexit\n");
		const std::string response = "id1: NAN\n";
		THEN("Info will be match to response")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == response);
		}
	}
	WHEN("Assign variable some value")
	{
		inputStream.str("let id1 = 2\nprint id1\nexit\n");
		const std::string response = "id1: 2.00\n";
		THEN("Info will be match to response")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == response);
		}
	}
	WHEN("Assign function some value")
	{
		inputStream.str("let id1 = 2\nfn fnId = id1\nprint fnId\nexit\n");
		const std::string response = "fnId: 2.00\n";
		THEN("Info will be match to response")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == response);
		}
	}
	WHEN("Assign function some expression")
	{
		inputStream.str("let id1 = 2\nfn fnId = id1 + id1\nprint fnId\nexit\n");
		const std::string addResponse = "fnId: 4.00\n";
		THEN("Info will be match to response")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == addResponse);
		}
		inputStream.str("let id1 = 3\nfn fnId = id1 * id1\nprint fnId\nexit\n");
		const std::string mulResponse = "fnId: 9.00\n";
		THEN("Info will be match to response")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == mulResponse);
		}
		inputStream.str("let id1 = 3\nfn fnId = id1 - id1\nprint fnId\nexit\n");
		const std::string subResponse = "fnId: 0.00\n";
		THEN("Info will be match to response")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == subResponse);
		}
		inputStream.str("let id1 = 3\nfn fnId = id1 / id1\nprint fnId\nexit\n");
		const std::string divResponse = "fnId: 1.00\n";
		THEN("Info will be match to response")
		{
			console.ProcessSession();
			REQUIRE(outputStream.str() == divResponse);
		}
	}
}