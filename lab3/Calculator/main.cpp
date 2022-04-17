// Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Calculator_lib/Calculator.h"
#include <iostream>

int main()
{
	Calculator calculator;

	bool status1 = calculator.AssignVariable("test", 1);
	bool status2 = calculator.AddVariable("test1");

    std::cout << "Hello World!\n";
}