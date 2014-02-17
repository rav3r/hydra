#include "UnitTest++/UnitTest++.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/*#include "Dock/DebugDraw.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "hydra");

	gDebugFont.loadFromFile("data/SourceSansPro.otf");

	Tab tab("tab");
	RootDock rootDock(0, 0, 800, 600, &tab);
	Tab left("left");
	rootDock[0].AddTabLeft(&left);
	Tab bottom("bottom");
	rootDock[0][1].AddTabBottom(&bottom);
	Tab bottom2("bottom2");
	rootDock[0][1].AddTabBottom(&bottom2);
	Tab left2("left2");
	rootDock[0][1][1].AddTabLeft(&left2);
	Tab project("project");
	rootDock[0][0].AddTab(&project);


	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			rootDock.OnEvent(event);

			if(event.type == sf::Event::Resized)
			{
				int minWidth = rootDock.GetMinWidth();
				int minHeight = rootDock.GetMinHeight();

				if((int)event.size.width < minWidth || (int)event.size.height < minHeight)
				{
					int newWidth  = std::max((int)event.size.width, minWidth);
					int newHeight = std::max((int)event.size.height, minHeight);
					window.setSize(sf::Vector2u(newWidth, newHeight));
				}

				rootDock.SetWidth(window.getSize().x);
				rootDock.SetHeight(window.getSize().y);
				rootDock.OnResize();
			}
		}

		window.clear(sf::Color(64, 64, 64));
		Dock_DebugDraw(rootDock, window);
		window.display();
	}

	return 0;
}*/