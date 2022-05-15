#pragma once
#include "Point.h"
#include "ISolidShape.h"
#include "ICanvas.h"

class Triangle : public ISolidShape
{
public:
	Triangle(const Point& vertex1, const Point& vertex2, const Point& vertex3, uint32_t fillColor, uint32_t outlineColor)
		: m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
		, m_fillColor(fillColor)
		, m_outlineColor(outlineColor)
	{
	}

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	uint32_t GetFillColor() const override;

	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

	void Draw(ICanvas& canvas) const override;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
	uint32_t m_fillColor;
	uint32_t m_outlineColor;
};
