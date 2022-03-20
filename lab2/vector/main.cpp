#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>

constexpr short FLOAT_PRECISION = 3;

bool ReadNumbers(std::istream& inputStream, std::vector<double>& outputVec);
void PrintVector(std::vector<double>& vec);
std::vector<double> MultiplyNegativeByMinMaxOfVector(std::vector<double>& vec);

int main(int argc, char* argv[])
{
	std::vector<double> numbers;
	bool status = ReadNumbers(std::cin, numbers);
	if (!status)
	{
		return 1;
	}

	std::vector<double> processedNumbers = MultiplyNegativeByMinMaxOfVector(numbers);
	PrintVector(processedNumbers);

	return 0;
}

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

void PrintVector(std::vector<double>& vec)
{
	std::cout << std::fixed << std::setprecision(FLOAT_PRECISION);
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<double>(std::cout, " "));
}

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

	std::for_each(vec.begin(), vec.end(), multiply);
	std::sort(resultVec.begin(), resultVec.end());

	return resultVec;
}