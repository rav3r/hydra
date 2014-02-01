#pragma once

#include "Tab.h"
#include "DockType.h"

class Dock
{
public:
	Dock(Dock* parent);

	virtual DockType GetType() = 0;

	virtual unsigned int GetChildCount() = 0;
	virtual Dock* GetDock(unsigned int index) = 0;
	Dock& operator[] (unsigned int index);
	virtual void DeleteDock(Dock* dock);
	virtual void Simplify(Dock* oldChild, Dock* newChild);

	virtual Dock* AddTabLeft(Tab* tab);
	virtual Dock* AddTabLeft(Dock* where, Tab* tab);

	virtual Dock* AddTabRight(Tab* tab);
	virtual Dock* AddTabRight(Dock* where, Tab* tab);

	virtual Dock* AddTabBottom(Tab* tab);
	virtual Dock* AddTabBottom(Dock* where, Tab* tab);

	virtual Tab* GetCurrentTab();

protected:
	Dock* mParent;

	friend class HorizontalDock;
	friend class VerticalDock;
	friend class RootDock;
};