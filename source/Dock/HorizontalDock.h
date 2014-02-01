#pragma once

#include "Tab.h"
#include "Dock.h"
#include <vector>

class HorizontalDock: public Dock
{
public:
	HorizontalDock(Dock* parent, Dock* firstChild);

	DockType GetType();

	unsigned int GetChildCount();
	Dock* GetDock(unsigned int index);

	Dock* AddTabLeft(Tab* tab);
	Dock* AddTabLeft(Dock* where, Tab* tab);

	Dock* AddTabRight(Tab* tab);
	Dock* AddTabRight(Dock* where, Tab* tab);

	Dock* AddTabBottom(Tab* tab);
	Dock* AddTabBottom(Dock* where, Tab* tab);

private:
	std::vector<Dock*> mDocks;
};