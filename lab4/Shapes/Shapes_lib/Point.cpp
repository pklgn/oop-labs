#include "pch.h"
#include "Point.h"

std::string Point::ToString(bool isEndLine) const
{
	std::ostringstream stringStream;
	stringStream << "x: " << x << " y: " << y;

	if (isEndLine)
	{
		stringStream << std::endl;
	}

	return stringStream.str();
}
