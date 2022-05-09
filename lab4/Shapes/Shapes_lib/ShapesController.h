#pragma once
#include "pch.h"
#include "IShape.h"
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
	void PrintShapesInfo(std::ostream& outputStream);
	IShape* GetMaxAreaShapePtr();
	IShape* GetMinPerimeterShapePtr();

private:
	bool AddCircle(std::ifstream& inputStream);
	bool AddTriangle(std::ifstream& inputStream);
	bool AddRectangle(std::ifstream& inputStream);
	bool AddLineSegment(std::ifstream& inputStream);

	std::vector<IShape> storage;
};
