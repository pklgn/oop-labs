#include "pch.h"
#include "Rectangle.h"

double Rectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double Rectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}

std::string Rectangle::ToString() const
{
	std::ostringstream stringStream;
	stringStream << "Shape type: rectangle" << std::endl
				 << "Area: " << GetArea() << std::endl
				 << "Perimeter: " << GetPerimeter() << std::endl
				 << "Outline color: " << std::hex << GetOutlineColor() << std::endl
				 << "Fill color: " << GetFillColor() << std::dec << std::endl
				 << "Left top vertex: " << m_leftTop.ToString()
				 << "Right bottom vertex: " << m_rightBottom.ToString()
				 << "Width: " << GetWidth() << std::endl
				 << "Height: " << GetHeight() << std::endl;

	return stringStream.str();
}

uint32_t Rectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t Rectangle::GetFillColor() const
{
	return m_fillColor;
}

Point Rectangle::GetLeftTop() const
{
	return m_leftTop;
}

Point Rectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double Rectangle::GetWidth() const
{
	return m_rightBottom.x - m_leftTop.x;
}

double Rectangle::GetHeight() const
{
	return m_leftTop.y - m_rightBottom.y;
}