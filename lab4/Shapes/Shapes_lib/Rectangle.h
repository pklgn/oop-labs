#pragma once
#include "Point.h"
#include "ISolidShape.h"

class Rectangle: public ISolidShape
{
public:
	Rectangle(const Point& leftTop, const Point& rightBottom, uint32_t fillColor, uint32_t outlineColor)
		: m_leftTop(leftTop)
		, m_rightBottom(rightBottom)
		, m_fillColor(fillColor)
		, m_outlineColor(outlineColor)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	Point GetLeftTop() const;
	Point GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	Point m_leftTop;
	Point m_rightBottom;
	uint32_t m_fillColor;
	uint32_t m_outlineColor;
};
