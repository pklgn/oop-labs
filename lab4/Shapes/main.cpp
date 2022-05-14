#include <iostream>
#include "Shapes_lib/ShapesController.h"


int main()
{
	ShapesController shapesController;
	size_t counter = 0;

	while (std::cin.eof())
	{
		++counter;
		if (!shapesController.ReadShape(std::cin))
		{
			std::cout << "Cannot read shape in " << counter << " position\n";
		}
	}

	std::cout << "Read shapes:\n";
	shapesController.PrintShapesInfo(std::cout);

	auto maxAreaShapeIt = *shapesController.FindMaxAreaShape();
	auto minPerimeterShapeIt = *shapesController.FindMinPerimeterShape();

	std::cout << "Max shape area shape\n" << maxAreaShapeIt->ToString();
	std::cout << "Min shape perimeter shape\n" << minPerimeterShapeIt->ToString();

	return 0;
}