#pragma once
#include "pch.h"
#include "Canvas.h"

void Canvas::DrawLine(const Point& from, const Point& to, uint32_t lineColor)
{
	sf::Color color(lineColor);
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(from.x, from.y), color),
		sf::Vertex(sf::Vector2f(to.x, to.y), color)
	};

	m_renderWindow.draw(line, 2, sf::Lines);

	return;
}

void Canvas::FillPolygon(const std::vector<Point>& points, uint32_t fillColor)
{
	sf::ConvexShape convex;

	convex.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); ++i)
	{
		convex.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}
	sf::Color color(fillColor);
	convex.setFillColor(color);

	m_renderWindow.draw(convex);

	return;
}

void Canvas::DrawCircle(const Point& center, double radius, uint32_t lineColor)
{
	sf::CircleShape circle;
	circle.setRadius(radius);
	circle.setPosition(center.x - radius, center.y + radius);
	
	circle.setFillColor(sf::Color::Transparent);
	sf::Color outlineColor(lineColor);
	circle.setOutlineColor(outlineColor);
	circle.setOutlineThickness(2);

	m_renderWindow.draw(circle);

	return;
}

void Canvas::FillCircle(const Point& center, double radius, uint32_t fillColor)
{
	sf::CircleShape circle;
	circle.setRadius(radius);
	circle.setPosition(center.x - radius, center.y + radius);

	sf::Color color(fillColor);
	circle.setFillColor(color);

	m_renderWindow.draw(circle);

	return;
}

sf::RenderWindow& Canvas::GetRenderWindow()
{
	return m_renderWindow;
}