#include "double_vector.h"
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

void PrintVector(std::vector<double>& vec, std::ostream& output)
{
	output << std::fixed << std::setprecision(FLOAT_PRECISION);
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<double>(output, " "));
	output << std::endl;
}

//const vec
std::vector<double> MultiplyNegativeByMinMaxOfVector(std::vector<double>& vec)
{
	auto bounds = std::minmax_element(vec.begin(), vec.end());

	std::vector<double> resultVec;
	auto multiply = [&](double element) {
		if (element < 0)
		{
			element *= *bounds.first * *bounds.second;
		}

		resultVec.push_back(element);
	};
	//использовать transform вместо for_each с back_insert_iterator
	std::for_each(vec.begin(), vec.end(), multiply);
	//sort вынести в printSorted вариант функции
	std::sort(resultVec.begin(), resultVec.end());

	return resultVec;
}