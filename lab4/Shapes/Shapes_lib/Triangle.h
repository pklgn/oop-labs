#pragma once
#include "Point.h"
#include "SolidShape.h"
#include "ICanvas.h"

class Triangle : public SolidShape
{
public:
	//inline static const std::string s_type = "Triangle";

	Triangle(const Point& vertex1, const Point& vertex2, const Point& vertex3, uint32_t fillColor, uint32_t outlineColor) 
		: SolidShape(fillColor, outlineColor)
		, m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

	void Draw(ICanvas& canvas) const override;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};
