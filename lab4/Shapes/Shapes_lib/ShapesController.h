#pragma once
#include "pch.h"
#include "IShape.h"
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "LineSegment.h"

class ShapesController
{
public:
	enum class Shape
	{
		Circle,
		Triangle,
		Rectangle,
		LineSegment,
	};

	bool ReadShape(std::istream& inputStream);
	void PrintShapesInfo(IShape& shape, std::ostream& outputStream) const;
	std::vector<IShape>::const_iterator FindMaxAreaShape() const;
	std::vector<IShape>::const_iterator FindMinPerimeterShape() const;

private:
	bool AddCircle(std::istream& inputStream);
	bool AddTriangle(std::istream& inputStream);
	bool AddRectangle(std::istream& inputStream);
	bool AddLineSegment(std::istream& inputStream);

	std::vector<IShape> m_storage;
};
