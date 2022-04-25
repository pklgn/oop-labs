#define CATCH_CONFIG_MAIN
#include "../Calculator_lib/Calculator.h"
#include "../Calculator_lib/CalculatorControlConsole.h"
#include "../../../catch2/catch.hpp"
#include <sstream>
// TODO: переместить IsIdentifier
// TODO: убрать Identifier заменить на std::string
// TODO: написать TEST_CASE
TEST_CASE("Create calculator")
{
	Calculator calculator;
	SECTION("Check the content before declaring new variables and functions")
	{
		REQUIRE(calculator.GetFunctions().size() == 0);
		REQUIRE(calculator.GetVariables().size() == 0);
	}
}

TEST_CASE("Define and assign a new variable")
{
	Calculator calculator;
	Calculator::Identifier identifier = "variable";
	Calculator::Value value = 1.234;
	SECTION("Add a single variable")
	{
		REQUIRE(calculator.DefineVariable(identifier));
		REQUIRE(calculator.GetVariables().size() == 1);
		REQUIRE(isnan(calculator.GetOperandValue(identifier).value()));
	}

	SECTION("Get value of the added variable")
	{
		REQUIRE(calculator.DefineVariable(identifier));
		REQUIRE(calculator.AssignVariable(identifier, value));
		REQUIRE(calculator.GetOperandValue(identifier).value() == value);
		REQUIRE(calculator.GetVariables().size() == 1);
	}

	SECTION("Declare a new variable with the same identifier")
	{
		REQUIRE(calculator.DefineVariable(identifier));
		Calculator::Identifier identifier2 = identifier;
		REQUIRE(!calculator.DefineVariable(identifier2));
		REQUIRE(calculator.GetVariables().size() == 1);
	}
}

TEST_CASE("Define a new function")
{
	Calculator calculator;
	Calculator::Identifier variableIdentifier = "variable";
	Calculator::Identifier functionIdentifier = "function";

	SECTION("Function is a nan value of another nan identifier")
	{
		REQUIRE(calculator.DefineVariable(variableIdentifier));
		REQUIRE(calculator.DefineFunction(functionIdentifier, variableIdentifier));
		REQUIRE(isnan(calculator.GetOperandValue(variableIdentifier).value()));
		REQUIRE(isnan(calculator.GetOperandValue(functionIdentifier).value()));
		REQUIRE(calculator.GetVariables().size() == 1);
		REQUIRE(calculator.GetFunctions().size() == 1);
	}

	SECTION("Function is a numeric value of another numeric variable identifier")
	{
		REQUIRE(calculator.AssignVariable(variableIdentifier, 1.23));
		REQUIRE(calculator.DefineFunction(functionIdentifier, variableIdentifier));
		REQUIRE(calculator.GetOperandValue(variableIdentifier).value() == 1.23);
		REQUIRE(calculator.GetOperandValue(functionIdentifier).value() == 1.23);
	}

	SECTION("Function is a numeric value of a math expression")
	{
		REQUIRE(calculator.AssignVariable(variableIdentifier, 1.23));
		REQUIRE(calculator.DefineFunction(functionIdentifier, 
			{ {variableIdentifier, variableIdentifier}, Calculator::Operation::Add }));
		REQUIRE(calculator.GetOperandValue(variableIdentifier).value() == 1.23);
		REQUIRE(calculator.GetOperandValue(functionIdentifier).value() == 2*1.23);
	}

	SECTION("Declare a new function with the same identifier")
	{
		REQUIRE(calculator.AssignVariable(variableIdentifier, 1.23));
		REQUIRE(calculator.DefineFunction(functionIdentifier,
			{ { variableIdentifier, variableIdentifier }, Calculator::Operation::Add }));
		REQUIRE(calculator.DefineFunction(functionIdentifier, variableIdentifier));
	}
}

TEST_CASE("Update function value with the new variable value")
{
	Calculator calculator;
	SECTION("Update identifier that function represents")
	{
		REQUIRE(calculator.AssignVariable("v", 42));
		REQUIRE(calculator.AssignVariable("variable", "v"));
		REQUIRE(calculator.DefineFunction("function", "v"));
		REQUIRE(calculator.AssignVariable("v", 43));
		REQUIRE(calculator.GetOperandValue("v").value() == 43);
		REQUIRE(calculator.GetOperandValue("variable").value() == 42);
		REQUIRE(calculator.GetOperandValue("function").value() == 43);
	}

	SECTION("Update function expression")
	{
		REQUIRE(calculator.DefineVariable("x"));
		REQUIRE(calculator.DefineVariable("y"));
		REQUIRE(calculator.DefineFunction("XPlusY", { { "x", "y" } }));
		REQUIRE(isnan(calculator.GetOperandValue("XPlusY").value()));
		REQUIRE(calculator.AssignVariable("x", 3));
		REQUIRE(calculator.AssignVariable("y", 4));
		REQUIRE(calculator.GetOperandValue("XPlusY").value() == 7);
		REQUIRE(calculator.AssignVariable("x", 10));
		REQUIRE(calculator.GetOperandValue("XPlusY").value() == 14);
	}
}

TEST_CASE("Define function with all operations of an expression")
{
	Calculator calculator;
	Calculator::Identifier variableIdentifier = "variable";
	Calculator::Identifier functionIdentifier = "function";

	SECTION("Create function with sum operation")
	{
		REQUIRE(calculator.AssignVariable(variableIdentifier, 1.23));
		REQUIRE(calculator.DefineFunction(functionIdentifier,
			{ { variableIdentifier, variableIdentifier }, Calculator::Operation::Add }));
		REQUIRE(calculator.GetOperandValue(variableIdentifier).value() == 1.23);
		REQUIRE(calculator.GetOperandValue(functionIdentifier).value() == 1.23 + 1.23);
	}
	SECTION("Create function with sub operation")
	{
		REQUIRE(calculator.AssignVariable(variableIdentifier, 1.23));
		REQUIRE(calculator.DefineFunction(functionIdentifier,
			{ { variableIdentifier, variableIdentifier }, Calculator::Operation::Sub }));
		REQUIRE(calculator.GetOperandValue(variableIdentifier).value() == 1.23);
		REQUIRE(calculator.GetOperandValue(functionIdentifier).value() == 1.23 - 1.23);
	}
	SECTION("Create function with mul operation")
	{
		REQUIRE(calculator.AssignVariable(variableIdentifier, 1.23));
		REQUIRE(calculator.DefineFunction(functionIdentifier,
			{ { variableIdentifier, variableIdentifier }, Calculator::Operation::Mul }));
		REQUIRE(calculator.GetOperandValue(variableIdentifier).value() == 1.23);
		REQUIRE(calculator.GetOperandValue(functionIdentifier).value() == 1.23 * 1.23);
	}
	SECTION("Create function with div operation")
	{
		REQUIRE(calculator.AssignVariable(variableIdentifier, 1.23));
		REQUIRE(calculator.DefineFunction(functionIdentifier,
			{ { variableIdentifier, variableIdentifier }, Calculator::Operation::Div }));
		REQUIRE(calculator.GetOperandValue(variableIdentifier).value() == 1.23);
		REQUIRE(calculator.GetOperandValue(functionIdentifier).value() == 1.23 / 1.23);
	}
	SECTION("Create function with div operation dividing by 0")
	{
		REQUIRE(calculator.AssignVariable(variableIdentifier, 0));
		REQUIRE(calculator.DefineFunction(functionIdentifier,
			{ { variableIdentifier, variableIdentifier }, Calculator::Operation::Div }));
		REQUIRE(calculator.GetOperandValue(variableIdentifier).value() == 0);
		REQUIRE(isnan(calculator.GetOperandValue(functionIdentifier).value()));
	}
}
TEST_CASE("Declare same id for operands different types")
{
	Calculator calculator;
	Calculator::Identifier identifier = "identifier";
	SECTION("Declare a new function with the same identifier")
	{
		REQUIRE(calculator.DefineVariable(identifier));
		REQUIRE(!calculator.DefineFunction(identifier, identifier));
		REQUIRE(calculator.GetVariables().size() == 1);
	}

	SECTION("Declare a new variable with the same identifier")
	{
		REQUIRE(calculator.DefineVariable(identifier));
		REQUIRE(calculator.DefineFunction("function", identifier));
		REQUIRE(!calculator.DefineVariable("function"));
		REQUIRE(calculator.GetVariables().size() == 1);
	}
}

TEST_CASE("Define and assign variable with control console")
{
	Calculator calculator;
	std::istringstream inputStream;
	std::ostringstream outputStream;
	CalculatorControlConsole console(inputStream, outputStream, calculator);

	SECTION("Define variable with NAN")
	{
		inputStream.str("var id1\nprint id1\nexit\n");
		const std::string response = "id1: NAN\n";
		console.ProcessSession();
		REQUIRE(outputStream.str() == response);
	}

	SECTION("Assign variable some value")
	{
		inputStream.str("let id1=2\nprint id1\nexit\n");
		const std::string response = "id1: 2.00\n";
		console.ProcessSession();
		REQUIRE(outputStream.str() == response);
	}
}

TEST_CASE("Define function with control console")
{
	Calculator calculator;
	std::istringstream inputStream;
	std::ostringstream outputStream;
	CalculatorControlConsole console(inputStream, outputStream, calculator);

	SECTION("Assign function some value")
	{
		inputStream.str("let id1=2\nfn fnId=id1\nprint fnId\nexit\n");
		const std::string response = "fnId: 2.00\n";
		console.ProcessSession();
		REQUIRE(outputStream.str() == response);
	}

	SECTION("Assign function some expression with addition")
	{
		inputStream.str("let id1=2\nfn fnId=id1+id1\nprint fnId\nexit\n");
		const std::string addResponse = "fnId: 4.00\n";
		console.ProcessSession();
		REQUIRE(outputStream.str() == addResponse);
	}

	SECTION("Assign function some expression with multiplication")
	{
		inputStream.str("let id1=3\nfn fnId=id1*id1\nprint fnId\nexit\n");
		const std::string mulResponse = "fnId: 9.00\n";
		console.ProcessSession();
		REQUIRE(outputStream.str() == mulResponse);
	}

	SECTION("Assign function some expression with subtraction")
	{
		inputStream.str("let id1=3\nfn fnId=id1-id1\nprint fnId\nexit\n");
		const std::string subResponse = "fnId: 0.00\n";
		console.ProcessSession();
		REQUIRE(outputStream.str() == subResponse);
	}

	SECTION("Assign function some expression with division")
	{
		inputStream.str("let id1=3\nfn fnId=id1/id1\nprint fnId\nexit\n");
		const std::string divResponse = "fnId: 1.00\n";
		console.ProcessSession();
		REQUIRE(outputStream.str() == divResponse);
	}
}

TEST_CASE("Give console application wrong commad")
{
	Calculator calculator;
	std::istringstream inputStream;
	std::ostringstream outputStream;
	CalculatorControlConsole console(inputStream, outputStream, calculator);

	SECTION("Incomplete command")
	{
		inputStream.str("var \nexit\n");
		const std::string response = "Can't define variable\n";
		console.ProcessSession();
		REQUIRE(outputStream.str() == response);
	}
	SECTION("Incomplete command")
	{
		inputStream.str("let x \nexit\n");
		const std::string response = "Can't assign variable\n";
		console.ProcessSession();
		REQUIRE(outputStream.str() == response);
	}
	SECTION("Incomplete command")
	{
		inputStream.str("fn func= \nexit\n");
		const std::string response = "Can't define function\n";
		console.ProcessSession();
		REQUIRE(outputStream.str() == response);
	}
	SECTION("Incomplete command")
	{
		inputStream.str("print func \nexit\n");
		const std::string response = "Cannot find such identifier\n"
									 "Can't print value of the specified identifier\n";
		console.ProcessSession();
		REQUIRE(outputStream.str() == response);
	}
}