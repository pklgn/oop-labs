#pragma once
#include "Point.h"
#include "ISolidShape.h"

class Triangle : ISolidShape
{
public:
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;
};
