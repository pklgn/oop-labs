#pragma once
#include "Shape.h"
#include "ISolidShape.h"

class SolidShape : public ISolidShape, public Shape
{
public:
	// const std::string& type
	SolidShape(uint32_t fillColor, uint32_t outlineColor)
		: Shape(outlineColor)
		, m_fillColor(fillColor)
	{
	}

	uint32_t GetFillColor() const override;

protected:
	uint32_t m_fillColor;
};
