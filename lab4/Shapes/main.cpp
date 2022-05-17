#include <iostream>
#include "Shapes_lib/ShapesController.h"
#include <SFML/Graphics.hpp>


int main()
{
	ShapesController shapesController;
	size_t counter = 0;

	while (!std::cin.eof())
	{
		if (!shapesController.ReadShape(std::cin) && !std::cin.eof())
		{
			std::cout << "Cannot read shape in " << counter + 1 << " position\n";
		}
		else if (!std::cin.eof())
		{
			++counter;
		}
	}

	if (counter > 0)
	{
		std::cout << "Read shapes:\n";
		shapesController.PrintShapesInfo(std::cout);

		auto maxAreaShapeIt = *shapesController.FindMaxAreaShape();
		auto minPerimeterShapeIt = *shapesController.FindMinPerimeterShape();

		std::cout << "Max area shape\n"
				  << maxAreaShapeIt->ToString() << std::endl;
		std::cout << "Min perimeter shape\n"
				  << minPerimeterShapeIt->ToString() << std::endl;
		// TODO: сделать, чтобы при изменении размеров окна сохранялись пропорции
		shapesController.DrawShapes(800, 600, "Shapes");
	}

	return 0;
}