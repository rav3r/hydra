#pragma once

#include "Dock.h"
#include "Tab.h"

class RootDock: public Dock
{
public:
	RootDock(int x, int y, int width, int height, Tab* tab);

	DockType GetType();

	unsigned int GetChildCount();
	Dock* GetDock(unsigned int index);
	void Simplify(Dock* oldChild, Dock* newChild);

	Dock* AddTabLeft(Dock* where, Tab* tab);
	Dock* AddTabRight(Dock* where, Tab* tab);
	Dock* AddTabBottom(Dock* where, Tab* tab);

	int GetPositionX();
	int GetPositionY();
	int GetWidth();
	int GetHeight();

private:
	int mX, mY;
	int mWidth, mHeight;

	Dock* mRootDock;
};