#pragma once
#include "IShape.h"
#include "Point.h"

class LineSegment : public IShape
{
public:
	Point GetStartPoint() const;
	Point GetEndPoint() const;
};
