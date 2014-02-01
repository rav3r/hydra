#include "VerticalDock.h"

#include "HorizontalDock.h"

DockType VerticalDock::GetType()
{
	return DockTypes::Vertical;
}

unsigned int VerticalDock::GetChildCount()
{
	return mDocks.size();
}

Dock* VerticalDock::GetDock(unsigned int index)
{
	return mDocks[index];
}

Dock* VerticalDock::AddTabLeft(Tab* tab)
{
	return mParent->AddTabLeft(this, tab);
}

Dock* VerticalDock::AddTabLeft(Dock* where, Tab* tab)
{
	int index = 0;
	for(; mDocks[index] != where; index++);

	Dock* tmp = mDocks[index];
	HorizontalDock* horizontalDock;
	mDocks[index] = horizontalDock = new HorizontalDock(this, tmp);
	return mDocks[index]->AddTabLeft(tab);
}

Dock* VerticalDock::AddTabRight(Tab* tab)
{
	return mParent->AddTabRight(this, tab);
}

Dock* VerticalDock::AddTabRight(Dock* where, Tab* tab)
{
	int index = 0;
	for(; mDocks[index] != where; index++);

	Dock* tmp = mDocks[index];
	HorizontalDock* horizontalDock;
	mDocks[index] = horizontalDock = new HorizontalDock(this, tmp);
	return mDocks[index]->AddTabRight(tab);
}