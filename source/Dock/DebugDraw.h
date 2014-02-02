#pragma once

#include "RootDock.h"

#include <SFML/Graphics.hpp>

void Dock_DebugDrawRecursively(Dock& dock, sf::RenderWindow& window)
{
	sf::RectangleShape rect;
	
	rect.setOutlineColor(sf::Color(255, 0, 0));
	rect.setFillColor(sf::Color(0, 255, 0));
	
	rect.setSize(sf::Vector2f((float)dock.GetWidth(), (float)dock.GetHeight()));
	rect.setPosition(sf::Vector2f((float)dock.GetPositionX(), (float)dock.GetPositionY()));
	rect.setOutlineThickness(1.0f);

	window.draw(rect);

	for(unsigned int i=0; i<dock.GetChildCount(); i++)
		Dock_DebugDrawRecursively(dock[i], window);
}

void Dock_DebugDraw(RootDock& root, sf::RenderWindow& window)
{
	sf::View view(sf::FloatRect(0, 0, (float)window.getSize().x, (float)window.getSize().y));

	window.setView(view);

	Dock_DebugDrawRecursively(root, window);
}