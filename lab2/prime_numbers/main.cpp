#include <iostream>
#include <set>
#include <vector>

constexpr int FIRST_PRIME_NUMBER = 2;
std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintPrimeNumbersSet(std::ostream& outputStream, std::set<int>& primes);

int main(int argc, char* argv[])
{
	std::set<int> primes = GeneratePrimeNumbersSet(atoi(argv[1]));
	if (!primes.empty())
	{
		PrintPrimeNumbersSet(std::cout, primes);
	}

	return 0;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> result{};

	if (upperBound < FIRST_PRIME_NUMBER)
	{
		return result;
	}

	std::vector<bool> primeVec(upperBound, true);
	size_t primeUpperBound = static_cast<size_t>(std::floor(sqrt(upperBound - 1)));
	for (size_t i = FIRST_PRIME_NUMBER; i < upperBound; i++)
	{
		if (primeVec[i] && i <= primeUpperBound)
		{
			for (size_t j = i * i; j < upperBound; j += i)
			{
				primeVec[j] = false;
			}
		}
	}

	for (size_t i = FIRST_PRIME_NUMBER; i < upperBound; i++)
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
	for (auto& prime: primes)
	{
		outputStream << prime << std::endl;
	}
}