#include "pch.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Circle.h"

double Circle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double Circle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string Circle::ToString() const
{
	std::ostringstream stringStream;
	stringStream << "Shape type: circle" << std::endl
				 << "Area: " << GetArea() << std::endl
				 << "Perimeter: " << GetPerimeter() << std::endl
				 << "Outline color: " << std::hex << GetOutlineColor() << std::endl
				 << "Fill color: " << GetFillColor() << std::dec << std::endl
				 << "Center Point: " << m_center.ToString()
				 << "Radius: " << m_radius << std::endl;

	return stringStream.str();
}

uint32_t Circle::GetOutlineColor() const
{
	return m_outlineColor;
}

double Circle::GetRadius() const
{
	return m_radius;
}

Point Circle::GetCenter() const
{
	return m_center;
}