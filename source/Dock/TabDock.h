#pragma once

#include "Tab.h"
#include "Dock.h"
#include <vector>

class TabDock: public Dock
{
public:
	TabDock(Dock* parent, Tab* tab);

	DockType GetType();

	unsigned int GetChildCount();
	Dock* GetDock(unsigned int index);

	void AddTab(Tab* tab);
	Tab* GetCurrentTab();

	Dock* AddTabLeft(Tab* tab);
	Dock* AddTabRight(Tab* tab);

private:
	std::vector<Tab*> mTabs;
};