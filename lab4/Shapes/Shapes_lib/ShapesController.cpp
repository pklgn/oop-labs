#include "pch.h"
#include "Point.h"
#include "Canvas.h"
#include "ShapesController.h"

bool ShapesController::ReadShape(std::istream& inputStream)
{
	std::string commandName;
	inputStream >> commandName;
	if (commandName == "circle")
	{
		return AddCircle(inputStream);
	}
	else if (commandName == "line")
	{
		return AddLineSegment(inputStream);
	}
	else if (commandName == "rectangle")
	{
		return AddRectangle(inputStream);
	}
	else if (commandName == "triangle")
	{
		return AddTriangle(inputStream);
	}
	
	return false;
}

void ShapesController::PrintShapesInfo(std::ostream& outputStream) const
{
	for (const auto& shape : m_storage)
	{
		outputStream << shape->ToString() << std::endl;
	}

	return;
}

std::vector<std::shared_ptr<IShape>>::const_iterator ShapesController::FindMaxAreaShape() const
{
	return std::max_element(m_storage.begin(), m_storage.end(),
		[](std::shared_ptr<IShape> first, std::shared_ptr<IShape> second) {
			return first->GetArea() < second->GetArea();
		});
}

std::vector<std::shared_ptr<IShape>>::const_iterator ShapesController::FindMinPerimeterShape() const
{
	return std::min_element(m_storage.begin(), m_storage.end(),
		[](std::shared_ptr<IShape> first, std::shared_ptr<IShape> second) {
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

	if (radius < 0)
	{
		return false;
	}

	m_storage.push_back(std::make_shared<Circle>(center, radius, fillColor, outlineColor));

	return true;
}

bool ShapesController::AddLineSegment(std::istream& inputStream)
{
	Point startPoint;
	Point endPoint;
	uint32_t outlineColor;

	inputStream >> startPoint >> endPoint >> std::hex >> outlineColor;
	if (inputStream.fail())
	{
		return false;
	}

	m_storage.push_back(std::make_shared<LineSegment>(startPoint, endPoint, outlineColor));

	return true;
}

bool ShapesController::AddRectangle(std::istream& inputStream)
{
	Point leftTop;
	Point rightBottom;
	uint32_t fillColor;
	uint32_t outlineColor;

	inputStream >> leftTop >> rightBottom >> std::hex >> fillColor >> outlineColor;
	if (inputStream.fail())
	{
		return false;
	}

	m_storage.push_back(std::make_shared<Rectangle>(leftTop, rightBottom, fillColor, outlineColor));

	return true;
}

bool ShapesController::AddTriangle(std::istream& inputStream)
{
	Point vertex1;
	Point vertex2;
	Point vertex3;
	uint32_t fillColor;
	uint32_t outlineColor;

	inputStream >> vertex1 >> vertex2 >> vertex3 >> std::hex >> fillColor >> outlineColor;
	if (inputStream.fail())
	{
		return false;
	}

	m_storage.push_back(std::make_shared<Triangle>(vertex1, vertex2, vertex3, fillColor, outlineColor));

	return true;
}

void ShapesController::DrawShapes(unsigned width, unsigned height, const std::string& windowTitle) const
{
	Canvas canvas(width, height, windowTitle);
	while (canvas.GetRenderWindow().isOpen())
	{
		sf::Event event;
		while (canvas.GetRenderWindow().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				canvas.GetRenderWindow().close();
		}

		canvas.GetRenderWindow().clear();

		for (const auto& shape : m_storage)
		{
			shape->Draw(canvas);
		}

		canvas.GetRenderWindow().display();
	}

	return;
}