#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape() = default;

	virtual uint32_t GetFillColor() const = 0;
};
