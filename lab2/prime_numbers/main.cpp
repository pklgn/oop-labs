#include <iostream>
#include <optional>
#include "prime_numbers_lib/prime_number_lib.h"

std::optional<int> GetParams(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: prime_numbers.exe <upperBound>\n";

		return std::nullopt;
	}

	int upperBound = atoi(argv[1]);

	if (upperBound < 2)
	{
		std::cout << "Minimum prime number equals 2\n";

		return std::nullopt;
	}

	return upperBound;
}

int main(int argc, char* argv[])
{
	const auto upperBound = GetParams(argc, argv);
	if (!upperBound.has_value())
	{
		return 1;
	}

	std::set<int> primes = GeneratePrimeNumbersSet(upperBound.value());
	if (!primes.empty())
	{
		PrintPrimeNumbersSet(std::cout, primes);
	}

	return 0;
}