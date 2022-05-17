#pragma once
#include "ICanvas.h"

class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;

	// TODO: объ€вить защищенный невиртуальный деструктор
};
