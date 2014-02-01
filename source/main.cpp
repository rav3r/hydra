#include "UnitTest++/UnitTest++.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Dock/DebugDraw.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "hydra");

	Tab tab("tab");
	RootDock rootDock(5, 5, 800, 600, &tab);
	Tab left("left");
	rootDock[0].AddTabLeft(&left);
	Tab bottom("bottom");
	rootDock[0][1].AddTabBottom(&bottom);

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		Dock_DebugDraw(rootDock, window);
		window.display();
	}

	return 0;
}