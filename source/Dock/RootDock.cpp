#include "RootDock.h"

#include "TabDock.h"
#include "HorizontalDock.h"

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

Dock* RootDock::AddTabLeft(Dock* where, Tab* tab)
{
	Dock* tmp = mRootDock;
	HorizontalDock* horizontalDock;
	mRootDock = horizontalDock = new HorizontalDock(this, tmp);
	return mRootDock->AddTabLeft(tab);
}

Dock* RootDock::AddTabRight(Dock* where, Tab* tab)
{
	Dock* tmp = mRootDock;
	HorizontalDock* horizontalDock;
	mRootDock = horizontalDock = new HorizontalDock(this, tmp);
	return mRootDock->AddTabRight(tab);
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