#pragma once
#include <vector>

bool ReadNumbers(std::istream& inputStream, std::vector<double>& outputVec);

void PrintVector(std::vector<double>& vec, std::ostream& output);

std::vector<double> MultiplyNegativeByMinMaxOfVector(std::vector<double>& vec);