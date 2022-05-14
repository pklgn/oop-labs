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

double Point::GetDistance(const Point& first, const Point& second)
{
	double xDistance = first.x - second.x;
	double yDistance = first.y - second.y;

	return sqrt(xDistance * xDistance + yDistance * yDistance);
}

std::istream& operator>>(std::istream& inputStream, Point& point)
{
	inputStream >> point.x >> point.y;

	return inputStream;
}