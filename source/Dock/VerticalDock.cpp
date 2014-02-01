#include "VerticalDock.h"

#include "HorizontalDock.h"
#include "TabDock.h"

#include <cassert>

VerticalDock::VerticalDock(Dock* parent, Dock* firstChild):
Dock(parent)
{
	mDocks.push_back(firstChild);
	firstChild->mParent = this;
}

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
	mDocks[index] = new HorizontalDock(this, tmp);
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
	mDocks[index] = new HorizontalDock(this, tmp);
	return mDocks[index]->AddTabRight(tab);
}

Dock* VerticalDock::AddTabBottom(Tab* tab)
{
	TabDock* tabDock = new TabDock(this, tab);
	mDocks.push_back(tabDock);
	
	return tabDock;
}

Dock* VerticalDock::AddTabBottom(Dock* where, Tab* tab)
{
	int index = 0;
	for(; mDocks[index] != where; index++);

	assert(index < (int)mDocks.size());

	mDocks.insert(mDocks.begin() + index + 1, new TabDock(this, tab));

	return mDocks[index + 1];
}