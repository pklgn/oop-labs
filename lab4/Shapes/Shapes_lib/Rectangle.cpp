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
	stringStream << std::fixed;
	stringStream.precision(3);

	stringStream << "Shape type: rectangle" << std::endl
				 << "Area: " << GetArea() << std::endl
				 << "Perimeter: " << GetPerimeter() << std::endl
				 << "Outline color: " << std::setfill('0') << std::setw(8) << std::hex << GetOutlineColor() << std::endl
				 << "Fill color: " << std::setfill('0') << std::setw(8) << GetFillColor() << std::dec << std::endl
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

void Rectangle::Draw(ICanvas& canvas) const
{
	Point rightTop = { m_rightBottom.x, m_leftTop.y };
	Point leftBottom = { m_leftTop.x, m_rightBottom.y };

	canvas.FillPolygon({ m_leftTop, rightTop, m_rightBottom, leftBottom }, m_fillColor);
	canvas.DrawLine(m_leftTop, rightTop, m_outlineColor);
	canvas.DrawLine(rightTop, m_rightBottom, m_outlineColor);
	canvas.DrawLine(m_rightBottom, leftBottom, m_outlineColor);
	canvas.DrawLine(leftBottom, m_leftTop, m_outlineColor);

	return;
}