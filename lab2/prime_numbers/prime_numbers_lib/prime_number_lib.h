#pragma once
#include <set>
#include <iostream>

std::set<int> GeneratePrimeNumbersSet(int upperBound);

void PrintPrimeNumbersSet(std::ostream& outputStream, std::set<int>& primes);