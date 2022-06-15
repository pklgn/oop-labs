#pragma once
#include <vector>
#include <algorithm>

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& vector, T& maxValue, Less const& less)
{
	if (vector.size() == 0)
	{
		return false;
	}

	auto currMaxValue = vector[0];

	std::for_each(vector.begin() + 1, vector.end(), [&](T const& element) {
		if (less(currMaxValue, element))
		{
			currMaxValue = element;
		}
	});

	maxValue = currMaxValue;

	return true;
}
