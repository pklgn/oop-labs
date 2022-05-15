#include "pch.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Circle.h"
#include "ICanvas.h"

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
	stringStream << std::fixed;
	stringStream.precision(3);

	stringStream << "Shape type: circle" << std::endl
				 << "Area: " << GetArea() << std::endl
				 << "Perimeter: " << GetPerimeter() << std::endl
				 << "Outline color: " << std::setfill('0') << std::setw(6) << std::hex << GetOutlineColor() << std::endl
				 << "Fill color: " << std::setfill('0') << std::setw(6) << GetFillColor() << std::dec << std::endl
				 << "Center Point: " << m_center.ToString()
				 << "Radius: " << m_radius << std::endl;

	return stringStream.str();
}

uint32_t Circle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Circle::GetFillColor() const
{
	return m_fillColor;
}

double Circle::GetRadius() const
{
	return m_radius;
}

Point Circle::GetCenter() const
{
	return m_center;
}

void Circle::Draw(ICanvas& canvas) const
{
	canvas.FillCircle(m_center, m_radius, m_fillColor);
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
}