#pragma once
#include "IShape.h"

class Shape : public virtual IShape
{
public:
	// const std::string& type
	Shape(uint32_t outlineColor)
		: m_outlineColor(outlineColor)
		//, m_type(type)
	{
	}

	uint32_t GetOutlineColor() const override;

protected:
	uint32_t m_outlineColor;
	//std::string m_type;
};