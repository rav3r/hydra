#pragma once

#include "Tab.h"
#include "Dock.h"
#include <vector>

class TabDock: public Dock
{
public:
	TabDock(Dock* parent, Tab* tab);

	DockType GetType();

	unsigned int GetChildCount();
	Dock* GetDock(unsigned int index);

	void AddTab(Tab* tab);
	void RemoveTab(Tab* tab);
	Tab* GetCurrentTab();

	Dock* AddTabLeft(Tab* tab);
	Dock* AddTabRight(Tab* tab);
	Dock* AddTabBottom(Tab* tab);

	bool OnEvent(const sf::Event& event);

	int GetMinWidth();
	int GetMinHeight();

	int GetCaptionWidth();

	unsigned int GetTabCount();
	Tab* GetTab(unsigned int index);
	
	bool IsTabDragged();
	DraggedTab GetDraggedTab();
	void FillDropArea(DraggedTab& draggedTab);
	bool OnDrop(DraggedTab draggedTab);

	void OnResize();


private:
	std::vector<Tab*> mTabs;
	unsigned int mCurrentTab;
	int mPressedTab;
	DraggedTab mDraggedTab;
	void InitDraggedTab(int mouseX, int mouseY);
};