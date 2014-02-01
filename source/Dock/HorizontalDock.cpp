#include "HorizontalDock.h"

#include "TabDock.h"
#include "VerticalDock.h"

#include <cassert>

HorizontalDock::HorizontalDock(Dock* parent, Dock* firstChild):
Dock(parent)
{
	mDocks.push_back(firstChild);
	firstChild->mParent = this;
}

DockType HorizontalDock::GetType()
{
	return DockTypes::Horizontal;
}

unsigned int HorizontalDock::GetChildCount()
{
	return mDocks.size();
}

Dock* HorizontalDock::GetDock(unsigned int index)
{
	return mDocks[index];
}

void HorizontalDock::DeleteDock(Dock* dock)
{
	int index = 0;
	for(; mDocks[index] != dock; index++);

	delete mDocks[index];
	mDocks.erase(mDocks.begin() + index);

	if(mDocks.size() == 1)
	{
		Dock* newChild = mDocks[0];
		mDocks.clear();
		mParent->Simplify(this, newChild);
	}
}

void HorizontalDock::Simplify(Dock* oldChild, Dock* newChild)
{
	int index = 0;
	for(; mDocks[index] != oldChild; index++);

	delete mDocks[index];
	mDocks[index] = newChild;
	mDocks[index]->mParent = this;
}

Dock* HorizontalDock::AddTabLeft(Tab* tab)
{
	TabDock* tabDock = new TabDock(this, tab);
	mDocks.insert(mDocks.begin(), tabDock);
	
	return tabDock;
}

Dock* HorizontalDock::AddTabLeft(Dock* where, Tab* tab)
{
	int index = 0;
	for(; mDocks[index] != where; index++);

	assert(index < (int)mDocks.size());

	mDocks.insert(mDocks.begin() + index, new TabDock(this, tab));

	return mDocks[index];
}

Dock* HorizontalDock::AddTabRight(Tab* tab)
{
	TabDock* tabDock = new TabDock(this, tab);
	mDocks.push_back(tabDock);
	
	return tabDock;
}

Dock* HorizontalDock::AddTabRight(Dock* where, Tab* tab)
{
	int index = 0;
	for(; mDocks[index] != where; index++);

	assert(index < (int)mDocks.size());

	mDocks.insert(mDocks.begin() + index + 1, new TabDock(this, tab));

	return mDocks[index + 1];
}


Dock* HorizontalDock::AddTabBottom(Tab* tab)
{
	return mParent->AddTabBottom(this, tab);
}

Dock* HorizontalDock::AddTabBottom(Dock* where, Tab* tab)
{
	int index = 0;
	for(; mDocks[index] != where; index++);

	Dock* tmp = mDocks[index];
	mDocks[index] = new VerticalDock(this, tmp);
	return mDocks[index]->AddTabBottom(tab);
}