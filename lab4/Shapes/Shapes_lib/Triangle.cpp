#include "pch.h"
#include "Triangle.h"

double Triangle::GetArea() const
{
	return sqrt(GetPerimeter() / 2 *
		Point::GetDistance(m_vertex1, m_vertex2) *
		Point::GetDistance(m_vertex2, m_vertex3) *
		Point::GetDistance(m_vertex1, m_vertex3));
}

double Triangle::GetPerimeter() const
{
	return Point::GetDistance(m_vertex1, m_vertex2) +
		Point::GetDistance(m_vertex2, m_vertex3) +
		Point::GetDistance(m_vertex1, m_vertex3);
}

std::string Triangle::ToString() const
{
	std::ostringstream stringStream;
	stringStream << "Shape type: triangle" << std::endl
				 << "Area: " << GetArea() << std::endl
				 << "Perimeter: " << GetPerimeter() << std::endl
				 << "Outline color: " << std::hex << GetOutlineColor() << std::endl
				 << "Fill color: " << GetFillColor() << std::dec << std::endl
				 << "First Vertex: " << m_vertex1.ToString()
				 << "Second Vertex: " << m_vertex2.ToString()
				 << "Third Vertex: " << m_vertex3.ToString();

	return stringStream.str();
}

uint32_t Triangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Triangle::GetFillColor() const
{
	return m_fillColor;
}

Point Triangle::GetVertex1() const
{
	return m_vertex1;
}

Point Triangle::GetVertex2() const
{
	return m_vertex2;
}

Point Triangle::GetVertex3() const
{
	return m_vertex3;
}