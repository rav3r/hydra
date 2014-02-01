#include "RootDock.h"

#include "TabDock.h"
#include "HorizontalDock.h"
#include "VerticalDock.h"

#include <cassert>

RootDock::RootDock(int x, int y, int width, int height, Tab* tab):
Dock(0), mX(x), mY(y), mWidth(width), mHeight(height), mRootDock(0)
{
	mRootDock = new TabDock(this, tab);
}

DockType RootDock::GetType()
{
	return DockTypes::Root;
}

unsigned int RootDock::GetChildCount()
{
	return 1;
}

Dock* RootDock::GetDock(unsigned int index)
{
	return mRootDock;
}

void RootDock::Simplify(Dock* oldChild, Dock* newChild)
{
	assert(oldChild == mRootDock);

	delete mRootDock;
	mRootDock = newChild;
	mRootDock->mParent = this;
}

Dock* RootDock::AddTabLeft(Dock* where, Tab* tab)
{
	Dock* tmp = mRootDock;
	mRootDock = new HorizontalDock(this, tmp);
	return mRootDock->AddTabLeft(tab);
}

Dock* RootDock::AddTabRight(Dock* where, Tab* tab)
{
	Dock* tmp = mRootDock;
	mRootDock = new HorizontalDock(this, tmp);
	return mRootDock->AddTabRight(tab);
}

Dock* RootDock::AddTabBottom(Dock* where, Tab* tab)
{
	Dock* tmp = mRootDock;
	mRootDock = new VerticalDock(this, tmp);
	return mRootDock->AddTabBottom(tab);
}

int RootDock::GetPositionX()
{
	return mX;
}

int RootDock::GetPositionY()
{
	return mY;
}

int RootDock::GetWidth()
{
	return mWidth;
}

int RootDock::GetHeight()
{
	return mHeight;
}