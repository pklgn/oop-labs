#include "pch.h"
#include "LineSegment.h"


double LineSegment::GetArea() const
{
	return 0.f;
}

double LineSegment::GetPerimeter() const
{
	return Point::GetDistance(m_startPoint, m_endPoint);
}

std::string LineSegment::ToString() const
{
	std::ostringstream stringStream;
	stringStream << std::fixed;
	stringStream.precision(3);

	stringStream << "Shape type: line segment" << std::endl
				 << "Area: " << GetArea() << std::endl
				 << "Perimeter: " << GetPerimeter() << std::endl
				 << "Outline color: " << std::setfill('0') << std::setw(8) << std::hex << GetOutlineColor() << std::dec << std::endl
				 << "Start point: " << m_startPoint.ToString()
				 << "End point: " << m_endPoint.ToString();

	return stringStream.str();
}

uint32_t LineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

Point LineSegment::GetStartPoint() const
{
	return m_startPoint;
}

Point LineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void LineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);

	return;
}