#pragma once

#include "RootDock.h"
#include "TabDock.h"
#include "Sizes.h"

#include <SFML/Graphics.hpp>

sf::Font gDebugFont;

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

	if(dock.GetType() == DockTypes::Tab)
	{
		TabDock& tabDock = (TabDock&)dock;

		sf::RectangleShape rect;

		rect.setFillColor(sf::Color(128, 128, 128));

		rect.setSize(sf::Vector2f((float)dock.GetWidth(), (float)CAPTION_HEIGHT));
		rect.setPosition(sf::Vector2f((float)dock.GetPositionX(), (float)dock.GetPositionY()));

		window.draw(rect);

		float posX = (float)dock.GetPositionX();
		for(unsigned int i=0; i<tabDock.GetTabCount(); i++)
		{
			sf::RectangleShape rect;

			bool current = tabDock.GetCurrentTab() == tabDock.GetTab(i);

			rect.setFillColor(current ? sf::Color(64, 64, 64) : sf::Color(128, 128, 128));
			rect.setOutlineColor(sf::Color(255, 255, 255));

			rect.setSize(sf::Vector2f(tabDock.GetCaptionWidth()-2, (float)CAPTION_HEIGHT-2));
			rect.setPosition(sf::Vector2f(posX+1, (float)dock.GetPositionY()+1));
			rect.setOutlineThickness(1.0f);

			window.draw(rect);

			sf::Text caption(tabDock.GetTab(i)->GetCaption(), gDebugFont, 16);
			caption.setPosition(sf::Vector2f(posX+2, (float)dock.GetPositionY()));
			window.draw(caption);

			posX += tabDock.GetCaptionWidth();
		}
	}
}

void Dock_DebugDraw(RootDock& root, sf::RenderWindow& window)
{
	sf::View view(sf::FloatRect(0, 0, (float)window.getSize().x, (float)window.getSize().y));

	window.setView(view);

	Dock_DebugDrawRecursively(root, window);
}