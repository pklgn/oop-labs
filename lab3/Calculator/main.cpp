// Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Calculator_lib/Calculator.h"
#include <iostream>

int main()
{
	Calculator calculator;

	bool status1 = calculator.AssignVariable("test1", 1);
	bool status2 = calculator.AssignVariable("test2", 2);
	bool status3 = calculator.DefineFunction("fn", "test");
	bool status4 = calculator.DefineFunction("fn1", { { "test2", "test1" }, Calculator::Operation::Add });

    std::cout << "Hello World!\n";
}