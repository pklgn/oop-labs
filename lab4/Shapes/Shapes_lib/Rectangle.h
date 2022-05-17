#pragma once
#include "Point.h"
#include "SolidShape.h"

class Rectangle: public SolidShape
{
public:
	//inline static const std::string s_type = "Rectangle";

	Rectangle(const Point& leftTop, const Point& rightBottom, uint32_t fillColor, uint32_t outlineColor)
		: SolidShape(fillColor, outlineColor)
		, m_leftTop(leftTop)
		, m_rightBottom(rightBottom)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	Point GetLeftTop() const;
	Point GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

	void Draw(ICanvas& canvas) const override;

private:
	Point m_leftTop;
	Point m_rightBottom;
};
