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

	std::vector<bool> primeVec(upperBound, true);
	size_t primeUpperBound = static_cast<size_t>(std::floor(sqrt(upperBound - 1)));
	// TODO: сделать цикл с 3 и шаг +2
	for (size_t i = FIRST_PRIME_NUMBER; i < upperBound; i++)
	{
		if (primeVec[i] && i <= primeUpperBound)
		{
			for (size_t j = i * i; j < static_cast<size_t>(upperBound); j += i)
			{
				primeVec[j] = false;
			}
		}
	}

	for (size_t i = FIRST_PRIME_NUMBER; i < static_cast<size_t>(upperBound); i++)
	{
		if (primeVec[i])
		{
			result.insert(static_cast<int>(i));
		}
	}

	return result;
}

void PrintPrimeNumbersSet(std::ostream& outputStream, std::set<int>& primes)
{
	// TODO: принимать по конст ссылке
	for (auto& prime : primes)
	{
		outputStream << prime << std::endl;
	}
}
