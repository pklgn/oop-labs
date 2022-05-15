#pragma once
#include "pch.h"
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
	void PrintShapesInfo(std::ostream& outputStream) const;
	std::vector<std::shared_ptr<IShape>>::const_iterator FindMaxAreaShape() const;
	std::vector<std::shared_ptr<IShape>>::const_iterator FindMinPerimeterShape() const;

	void DrawShapes(unsigned width, unsigned height, const std::string& windowTitle) const;

private:
	bool AddCircle(std::istream& inputStream);
	bool AddTriangle(std::istream& inputStream);
	bool AddRectangle(std::istream& inputStream);
	bool AddLineSegment(std::istream& inputStream);

	std::vector<std::shared_ptr<IShape>> m_storage;
};
