// Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Calculator_lib/Calculator.h"
#include "Calculator_lib/CalculatorControlConsole.h"
#include <iostream>

int main()
{
	Calculator calculator;

	CalculatorControlConsole calculatorControlConsole(std::cin, std::cout, calculator);
	calculatorControlConsole.ProcessSession();
}