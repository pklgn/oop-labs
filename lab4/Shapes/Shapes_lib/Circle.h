#pragma once
#include "ISolidShape.h"
#include "Point.h"

class Circle : ISolidShape
{
public:
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
