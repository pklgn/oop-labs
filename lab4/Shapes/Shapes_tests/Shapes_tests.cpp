#pragma once
#define CATCH_CONFIG_MAIN
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../../../catch2/catch.hpp"
#include "../Shapes_lib/Circle.h"
#include "../Shapes_lib/Triangle.h"
#include "../Shapes_lib/LineSegment.h"
#include "../Shapes_lib/ShapesController.h"
#include "../Shapes_lib/Rectangle.h"

TEST_CASE("Create basic triangle")
{
	Point vertex1 = { 0, 0 };
	Point vertex2 = { 0, 4 };
	Point vertex3 = { 3, 0 };

	uint32_t fillColor = 0xff01ffff;
	uint32_t outlineColor = 0xff0030ff;

	SECTION("Add a new triangle object")
	{
		Triangle triangle(vertex1, vertex2, vertex3, fillColor, outlineColor);
		REQUIRE(triangle.GetArea() == 6.0);
		REQUIRE(triangle.GetFillColor() == fillColor);
		REQUIRE(triangle.GetOutlineColor() == outlineColor);
		REQUIRE(triangle.GetVertex1() == vertex1);
		REQUIRE(triangle.GetVertex2() == vertex2);
		REQUIRE(triangle.GetVertex3() == vertex3);
		REQUIRE(triangle.GetPerimeter() == 12.0);
	}
}

TEST_CASE("Create basic circle")
{
	Point center = { 0, 3 };
	double raduis = 3.5;

	uint32_t fillColor = 0xff00ffff;
	uint32_t outlineColor = 0xff0000ff;

	SECTION("Add new circle object")
	{
		Circle circle(center, raduis, fillColor, outlineColor);
		REQUIRE(circle.GetArea() == M_PI * raduis * raduis);
		REQUIRE(circle.GetCenter() == center);
		REQUIRE(circle.GetFillColor() == fillColor);
		REQUIRE(circle.GetOutlineColor() == outlineColor);
		REQUIRE(circle.GetPerimeter() == 2 * M_PI * raduis);
	}
}

TEST_CASE("Create basic line")
{
	Point startPoint = { 10, 3.5 };
	Point endPoint = { 1.5, -5.5 };

	uint32_t outlineColor = 0xff0000ff;

	SECTION("Add new line object")
	{
		double dx = startPoint.x - endPoint.x;
		double dy = startPoint.y - endPoint.y;
		LineSegment line(startPoint, endPoint, outlineColor);
		REQUIRE(line.GetArea() == 0);
		REQUIRE(line.GetPerimeter() == sqrt(dx * dx + dy * dy));
		REQUIRE(line.GetOutlineColor() == outlineColor);
	}
}


TEST_CASE("Read from stream")
{
	ShapesController shapeController;

	SECTION("Read rectangle data")
	{
		std::istringstream stringStream("rectangle 150 150 450 350 ffffffee ffff00ff");
		REQUIRE(shapeController.ReadShape(stringStream));
	}

	SECTION("Read circle data")
	{
		std::istringstream stringStream("circle 350 150 50 4db4f0ff 000000ff");
		REQUIRE(shapeController.ReadShape(stringStream));
	}

	SECTION("Read triangle data")
	{
		std::istringstream stringStream("triangle 450 150 600 250 450 350 4df068ee 4df068ff");
		REQUIRE(shapeController.ReadShape(stringStream));
	}

	SECTION("Read line data")
	{
		std::istringstream stringStream("line 400 150 400 75 ffffffff");
		REQUIRE(shapeController.ReadShape(stringStream));
	}

	SECTION("Read wrong data")
	{
		std::istringstream stringStream("exit 400 150 400 75 ffffffff");
		REQUIRE(!shapeController.ReadShape(stringStream));
	}

	SECTION("There is no data")
	{
		std::ostringstream outputStream;
		shapeController.PrintShapesInfo(outputStream);
		REQUIRE(outputStream.str() == "There are no shapes\n");
	}
}

TEST_CASE("Find min and max values")
{
	ShapesController shapesController;

	SECTION("Find max area shape")
	{
		std::istringstream stringStream("rectangle 150 350 450 150 ffffffee ffff00ff\ncircle 350 150 50 4db4f0ff 000000ff\ntriangle 450 150 600 250 450 350 4df068ee 4df068ff\nline 400 150 400 75 ffffffff");

		while (!stringStream.eof())
		{
			shapesController.ReadShape(stringStream); 
		}

		REQUIRE(shapesController.FindMaxAreaShape()->get()->ToString() == "Shape type: rectangle\nArea: 60000.000\nPerimeter: 1000.000\nOutline color: ffff00ff\nFill color: ffffffee\nLeft top vertex: x: 150.000 y: 350.000\nRight bottom vertex: x: 450.000 y: 150.000\nWidth: 300.000\nHeight: 200.000\n");
	}

	SECTION("Find min perimeter shape")
	{
		std::istringstream stringStream("rectangle 150 350 450 150 ffffffee ffff00ff\ncircle 350 150 50 4db4f0ff 000000ff\ntriangle 450 150 600 250 450 350 4df068ee 4df068ff\nline 400 150 400 75 ffffffff");

		while (!stringStream.eof())
		{
			shapesController.ReadShape(stringStream);
		}

		REQUIRE(shapesController.FindMinPerimeterShape()->get()->ToString() == "Shape type: line segment\nArea: 0.000\nPerimeter: 75.000\nOutline color: ffffffff\nStart point: x: 400.000 y: 150.000\nEnd point: x: 400.000 y: 75.000\n");
	}
}