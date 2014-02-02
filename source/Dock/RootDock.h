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
	int ComputeChildPositionX(Dock* dock);
	int ComputeChildPositionY(Dock* dock);
	int ComputeChildWidth(Dock* dock);
	int ComputeChildHeight(Dock* dock);

	void SetWidth(int width);
	void SetHeight(int height);

	bool OnEvent(const sf::Event& event);

	int GetMinWidth();
	int GetMinHeight();

private:
	int mX, mY;
	int mWidth, mHeight;

	Dock* mRootDock;
};