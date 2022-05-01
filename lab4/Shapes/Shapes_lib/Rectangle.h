#pragma once
#include "Point.h"
#include "ISolidShape.h"

class Rectangle: ISolidShape
{
public:
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	Point GetLeftTop() const;
	Point GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
};
