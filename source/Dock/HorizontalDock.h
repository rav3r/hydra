#pragma once

#include "Tab.h"
#include "Dock.h"
#include <vector>

class HorizontalDock: public Dock
{
public:
	HorizontalDock(Dock* parent, Dock* firstChild);

	DockType GetType();

	unsigned int GetChildCount();
	Dock* GetDock(unsigned int index);
	void DeleteDock(Dock* dock);
	void Simplify(Dock* oldChild, Dock* newChild);

	Dock* AddTabLeft(Tab* tab);
	Dock* AddTabLeft(Dock* where, Tab* tab);

	Dock* AddTabRight(Tab* tab);
	Dock* AddTabRight(Dock* where, Tab* tab);

	Dock* AddTabBottom(Tab* tab);
	Dock* AddTabBottom(Dock* where, Tab* tab);

	int ComputeChildPositionX(Dock* dock);
	int ComputeChildPositionY(Dock* dock);
	int ComputeChildWidth(Dock* dock);
	int ComputeChildHeight(Dock* dock);

private:
	std::vector<Dock*> mDocks;
};