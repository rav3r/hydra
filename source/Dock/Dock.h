#pragma once

#include "Tab.h"
#include "DockType.h"
#include "DraggedTab.h"

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

	virtual void AddTab(Tab* tab);
	virtual void RemoveTab(Tab* tab);
	virtual Tab* GetCurrentTab();

	virtual int GetPositionX();
	virtual int GetPositionY();
	virtual int GetWidth();
	virtual int GetHeight();

	virtual int ComputeChildPositionX(Dock* dock);
	virtual int ComputeChildPositionY(Dock* dock);
	virtual int ComputeChildWidth(Dock* dock);
	virtual int ComputeChildHeight(Dock* dock);

	Dock* GetRoot();

	virtual bool OnMouseMove(int x, int y) = 0;
	virtual bool OnLeftDown(int x, int y) = 0;
	virtual bool OnLeftUp(int x, int y) = 0;

	virtual int GetMinWidth() = 0;
	virtual int GetMinHeight() = 0;

	virtual bool IsTabDragged() = 0;
	virtual DraggedTab GetDraggedTab() = 0;
	virtual void FillDropArea(DraggedTab& draggedTab) = 0;
	virtual bool OnDrop(DraggedTab draggedTab) = 0;

	virtual void OnResize() = 0;

protected:
	Dock* mParent;

	int mSize;

	friend class HorizontalDock;
	friend class VerticalDock;
	friend class RootDock;
	friend class TabDock;
};