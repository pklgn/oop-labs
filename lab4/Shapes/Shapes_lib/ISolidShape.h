#pragma once
#include "IShape.h"

class ISolidShape : IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;
};
