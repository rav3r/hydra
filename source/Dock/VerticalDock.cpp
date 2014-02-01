#include "VerticalDock.h"

#include "HorizontalDock.h"
#include "TabDock.h"
#include "Sizes.h"

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

void VerticalDock::DeleteDock(Dock* dock)
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

void VerticalDock::Simplify(Dock* oldChild, Dock* newChild)
{
	int index = 0;
	for(; mDocks[index] != oldChild; index++);

	delete mDocks[index];
	mDocks[index] = newChild;
	mDocks[index]->mParent = this;
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

int VerticalDock::ComputeChildPositionX(Dock* dock)
{
	return GetPositionX();
}

int VerticalDock::ComputeChildPositionY(Dock* dock)
{
	int index = 0;
	int pos = GetPositionY();
	for(; mDocks[index] != dock; index++)
	{
		pos += mDocks[index]->mSize;
		pos += SPLITTER_SIZE;
	}

	return pos;
}

int VerticalDock::ComputeChildWidth(Dock* dock)
{
	return GetWidth();
}

int VerticalDock::ComputeChildHeight(Dock* dock)
{
	if(dock != mDocks.back())
		return dock->mSize;

	return GetHeight() - ComputeChildPositionY(dock) + GetPositionY();
}