#pragma once
#include "Point.h"
#include "SolidShape.h"
#include "ICanvas.h"

class Circle : public SolidShape
{
public:
	//inline static const std::string s_type = "Circle";

	Circle(const Point& center, double radius, uint32_t fillColor, uint32_t outlineColor)
		: SolidShape(fillColor, outlineColor)
		, m_center(center)
		, m_radius(radius)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	Point GetCenter() const;
	double GetRadius() const;

	void Draw(ICanvas& canvas) const override;

	//TODO: использовать шаблонный метод

private:
	Point m_center;
	double m_radius;
};
