#include <iostream>
#include <iomanip>
#include "vector_lib/vector_lib.h"

int main(int argc, char* argv[])
{
	std::vector<double> numbers;
	bool status = ReadNumbers(std::cin, numbers);
	if (!status)
	{
		return 1;
	}

	std::vector<double> processedNumbers = MultiplyNegativeByMinMaxOfVector(numbers);
	PrintVector(processedNumbers, std::cout);

	return 0;
}