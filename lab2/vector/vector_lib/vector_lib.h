#pragma once
#include <vector>

bool ReadNumbers(std::istream& inputStream, std::vector<double>& outputVec);

void PrintSortedVector(const std::vector<double>& vec, std::ostream& output);

std::vector<double> MultiplyNegativeByMinMaxOfVector(const std::vector<double>& vec);