#include "TabDock.h"

#include <cassert>

TabDock::TabDock(Dock* parent, Tab* tab):
Dock(parent)
{
	AddTab(tab);
}

DockType TabDock::GetType()
{
	return DockTypes::Tab;
}

unsigned int TabDock::GetChildCount()
{
	return 0;
}

Dock* TabDock::GetDock(unsigned int index)
{
	return 0;
}

void TabDock::AddTab(Tab* tab)
{
	mTabs.push_back(tab);
}

Tab* TabDock::GetCurrentTab()
{
	return mTabs[0];
}

Dock* TabDock::AddTabLeft(Tab* tab)
{
	return mParent->AddTabLeft(this, tab);
}

Dock* TabDock::AddTabRight(Tab* tab)
{
	return mParent->AddTabRight(this, tab);
}

Dock* TabDock::AddTabBottom(Tab* tab)
{
	return mParent->AddTabBottom(this, tab);
}