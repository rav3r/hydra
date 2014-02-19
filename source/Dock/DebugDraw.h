#pragma once

#include "RootDock.h"
#include "TabDock.h"
#include "Sizes.h"

#include <SFML/Graphics.hpp>

sf::Font gDebugFont;
sf::Texture gGuiTexture;

void DrawGUIElement(sf::RenderTarget& target, sf::Texture& texture,
	int bt, int bb, int bl, int br,
	int tx, int ty, int twidth, int theight,
	int x, int y, int width, int height)
{
	const unsigned int triangleStripVextexCount = 24;
	const unsigned int triangleStripVertexOrder[triangleStripVextexCount] = {0, 4, 1, 5, 2, 6, 3, 7, 7, 11, 6, 10, 5, 9 ,4 ,8, 8 ,12 ,9 ,13, 10 ,14, 11,15};

	unsigned int x_pos[4] = {x, x + bl, x + width  - br, x + width};
	unsigned int y_pos[4] = {y, y + bt, y + height - bb, y + height};
	sf::Vector2f verticesPosition[16];

	unsigned int x_textCoord[4] = {tx, tx+bl, tx+twidth  - br, tx+twidth};
	unsigned int y_textCoord[4] = {ty, ty+bt, ty+theight - bb, ty+theight};
	sf::Vector2f verticesTextCoord[16];

	for(int i = 0; i< 4;i++)
	{
		for(int j = 0; j< 4;j++)
		{
			verticesPosition[i+4*j] = sf::Vector2f(x_pos[i],y_pos[j]);
			verticesTextCoord[i+4*j] = sf::Vector2f(x_textCoord[i],y_textCoord[j]);
		}
	}

	sf::VertexArray vertexArray(sf::TrianglesStrip, 24);

	for(int i = 0; i<triangleStripVextexCount;i++)
	{
		vertexArray[ i].position  = verticesPosition [ triangleStripVertexOrder[i]];
		vertexArray[ i].texCoords = verticesTextCoord[ triangleStripVertexOrder[i]];
	}

	sf::RenderStates states;
	states.texture = &texture;

	target.draw(vertexArray, states);
}

void Dock_DebugDrawRecursively(Dock& dock, sf::RenderTarget& window)
{
	if(dock.GetType() == DockTypes::Tab)
	{
		DrawGUIElement(window, gGuiTexture, CAPTION_HEIGHT, 2, 2, 2, 0, 0, 127, 127, dock.GetPositionX(), dock.GetPositionY(), dock.GetWidth(), dock.GetHeight());
	}

	for(unsigned int i=0; i<dock.GetChildCount(); i++)
		Dock_DebugDrawRecursively(dock[i], window);

	if(dock.GetType() == DockTypes::Tab)
	{
		TabDock& tabDock = (TabDock&)dock;

		float posX = (float)dock.GetPositionX();
		for(unsigned int i=0; i<tabDock.GetTabCount(); i++)
		{
			bool current = tabDock.GetCurrentTab() == tabDock.GetTab(i);

			if(current)
				DrawGUIElement(window, gGuiTexture, 2, 2, 2, 2, 0, 384, 63, 24, posX, dock.GetPositionY(), tabDock.GetCaptionWidth(), CAPTION_HEIGHT);

			sf::Text caption(tabDock.GetTab(i)->GetCaption(), gDebugFont, 16);
			float startX = tabDock.GetCaptionWidth() / 2 - caption.getLocalBounds().width/2.0f;
			caption.setPosition(sf::Vector2f(posX+startX, (float)dock.GetPositionY()));
			window.draw(caption);

			posX += tabDock.GetCaptionWidth();
		}
	}
}

void Dock_DebugDraw(RootDock& root, sf::RenderTarget& window, int width, int height)
{
	sf::View view(sf::FloatRect(0, 0, (float)width, (float)height));

	window.setView(view);

	Dock_DebugDrawRecursively(root, window);

	if(root.IsTabDragged())
	{
		DraggedTab draggedTab = root.GetDraggedTab();

		draggedTab.showArea = false;
		root.FillDropArea(draggedTab);

		if(draggedTab.showArea)
		{
			sf::RectangleShape rect;

			rect.setFillColor(sf::Color(255, 255, 255, 128));

			rect.setSize(sf::Vector2f((float)draggedTab.areaWidth, (float)draggedTab.areaHeight));
			rect.setPosition(sf::Vector2f((float)draggedTab.areaX, (float)draggedTab.areaY));

			window.draw(rect);
		}
		
		sf::RectangleShape rect;

		rect.setFillColor(sf::Color(255, 255, 255, 128));

		rect.setSize(sf::Vector2f((float)draggedTab.width, (float)draggedTab.height));
		rect.setPosition(sf::Vector2f((float)draggedTab.x - draggedTab.width/2, (float)draggedTab.y - draggedTab.height));

		window.draw(rect);
	}
}