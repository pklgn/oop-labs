#pragma once
#include "Shape.h"
#include "Point.h"

class LineSegment : public Shape
{
public:
	//inline static const std::string s_type = "LineSegment";

	LineSegment(Point& startPoint, Point& endPoint, uint32_t outlineColor)
		: Shape(outlineColor)
		, m_startPoint(startPoint)
		, m_endPoint(endPoint)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	Point GetStartPoint() const;
	Point GetEndPoint() const;

	void Draw(ICanvas& canvas) const override;

private:
	Point m_startPoint;
	Point m_endPoint;
};
