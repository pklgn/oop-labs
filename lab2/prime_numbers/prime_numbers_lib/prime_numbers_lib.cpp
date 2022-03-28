// prime_numbers_lib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include <vector>

constexpr int FIRST_PRIME_NUMBER = 2;

std::set<int> GeneratePrimeNumbersSet(const int upperBound)
{
	std::set<int> result{};

	if (upperBound < FIRST_PRIME_NUMBER)
	{
		return result;
	}
	result.insert(FIRST_PRIME_NUMBER);

	std::vector<bool> primeVec(upperBound + 1, true);
	size_t primeUpperBound = static_cast<size_t>(std::floor(sqrt(upperBound - 1)));
	// TODO: сделать цикл с 3 и шаг +2
	for (size_t i = FIRST_PRIME_NUMBER + 1; i < upperBound + 1; i += 2)
	{
		if (primeVec[i])
		{
			result.insert(static_cast<int>(i));

			if (i <= primeUpperBound)
			{

				for (size_t j = i * i; j <= static_cast<size_t>(upperBound); j += i)
				{
					primeVec[j] = false;
				}
			}
		}
	}

	return result;
}

void PrintPrimeNumbersSet(std::ostream& outputStream, std::set<int>& primes)
{
	// TODO: принимать по конст ссылке
	for (const auto& prime : primes)
	{
		outputStream << prime << std::endl;
	}
}
