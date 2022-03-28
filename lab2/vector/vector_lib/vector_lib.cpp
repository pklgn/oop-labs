// vector_lib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "vector_lib.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

constexpr short FLOAT_PRECISION = 3;

bool ReadNumbers(std::istream& inputStream, std::vector<double>& outputVec)
{
	std::copy(std::istream_iterator<double>(inputStream), std::istream_iterator<double>(),
		std::back_inserter(outputVec));

	if (inputStream.fail() && !inputStream.eof())
	{
		std::cout << "Invalid number value was found\n";

		return false;
	}

	return true;
}

void PrintSortedVector(const std::vector<double>& vec, std::ostream& output)
{
	// TODO: sort вынести в PrintSortedVector вариант функции
	std::vector<double> tempVec;
	std::copy(vec.begin(), vec.end(), std::back_inserter(tempVec));
	std::sort(tempVec.begin(), tempVec.end());

	output << std::fixed << std::setprecision(FLOAT_PRECISION);
	std::copy(tempVec.begin(), tempVec.end(), std::ostream_iterator<double>(output, " "));
	output << std::endl;
}

// TODO: const vec
std::vector<double> MultiplyNegativeByMinMaxOfVector(const std::vector<double>& vec)
{
	auto bounds = std::minmax_element(vec.begin(), vec.end());

	std::vector<double> resultVec;
	auto multiply = [&](double element) -> double {
		if (element < 0)
		{
			element *= *bounds.first * *bounds.second;
		}

		return element;
	};

	// TODO: использовать transform вместо for_each с back_insert_iterator
	std::transform(vec.begin(), vec.end(), std::back_inserter(resultVec), multiply);

	return resultVec;
}
