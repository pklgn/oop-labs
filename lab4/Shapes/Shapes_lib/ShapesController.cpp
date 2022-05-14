#include "pch.h"
#include "Point.h"
#include "ShapesController.h"

bool ShapesController::ReadShape(std::istream& inputStream)
{
	std::string shapeName;
	if (shapeName == "circle")
	{
		AddCircle(inputStream);
	}
	else if (shapeName == "line")
	{
		AddLineSegment(inputStream);
	}
	else if (shapeName == "rectangle")
	{
		AddRectangle(inputStream);
	}
	else if (shapeName == "triangle")
	{
		AddTriangle(inputStream);
	}
	else
	{
		return false;
	}

	return true;
}

void ShapesController::PrintShapesInfo(std::ostream& outputStream) const
{
	for (const auto& shape : m_storage)
	{
		outputStream << shape->ToString() << std::endl;
	}

	return;
}

std::vector<IShape*>::const_iterator ShapesController::FindMaxAreaShape() const
{
	return std::max_element(m_storage.begin(), m_storage.end(), [](IShape* first, IShape* second) {
		return first->GetArea() < second->GetArea();
	});
}

std::vector<IShape*>::const_iterator ShapesController::FindMinPerimeterShape() const
{
	return std::min_element(m_storage.begin(), m_storage.end(), [](IShape* first, IShape* second) {
		return first->GetPerimeter() < second->GetPerimeter();
	});
}

bool ShapesController::AddCircle(std::istream& inputStream)
{
	Point center;
	double radius;
	uint32_t fillColor;
	uint32_t outlineColor;

	inputStream >> center >> radius >> std::hex >> fillColor >> outlineColor;
	if (inputStream.fail())
	{
		return false;
	}

	Circle circle(center, radius, fillColor, outlineColor);
	m_storage.push_back(&circle);

	return true;
}

bool ShapesController::AddLineSegment(std::istream& inputStream)
{
	Point startPoint;
	Point endPoint;
	uint32_t outlineColor;

	inputStream >> startPoint >> endPoint >> outlineColor;
	if (inputStream.fail())
	{
		return false;
	}

	LineSegment line(startPoint, endPoint, outlineColor);
	m_storage.push_back(&line);

	return true;
}

bool ShapesController::AddRectangle(std::istream& inputStream)
{
	Point leftTop;
	Point rightBottom;
	uint32_t fillColor;
	uint32_t outlineColor;

	inputStream >> leftTop >> rightBottom >> fillColor >> outlineColor;
	if (inputStream.fail())
	{
		return false;
	}

	Rectangle rectangle(leftTop, rightBottom, fillColor, outlineColor);
	m_storage.push_back(&rectangle);

	return true;
}

bool ShapesController::AddTriangle(std::istream& inputStream)
{
	Point vertex1;
	Point vertex2;
	Point vertex3;
	uint32_t fillColor;
	uint32_t outlineColor;

	inputStream >> vertex1 >> vertex2 >> vertex3 >> fillColor >> outlineColor;
	if (inputStream.fail())
	{
		return false;
	}

	Triangle triangle(vertex1, vertex2, vertex3, fillColor, outlineColor);
	m_storage.push_back(&triangle);

	return true;
}