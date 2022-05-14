#pragma once
class Point
{
public:
	double x;
	double y;

	std::string ToString(bool isEndLine = true) const;
	static double GetDistance(const Point& firstPoint, const Point& secondPoint);
	friend std::istream& operator>>(std::istream& inputStream, Point& point);
};
