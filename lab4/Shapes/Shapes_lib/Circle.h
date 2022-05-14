#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Circle : public ISolidShape
{
public:
	Circle(const Point& center, double radius, uint32_t fillColor, uint32_t outlineColor)
		: m_center(center)
		, m_radius(radius)
		, m_fillColor(fillColor)
		, m_outlineColor(outlineColor)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	Point GetCenter() const;
	double GetRadius() const;

private:
	Point m_center;
	double m_radius;
	uint32_t m_fillColor;
	uint32_t m_outlineColor;
};
