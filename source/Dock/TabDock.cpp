#include "TabDock.h"
#include "Sizes.h"

#include <cassert>

TabDock::TabDock(Dock* parent, Tab* tab):
Dock(parent), mCurrentTab(0), mPressedTab(-1)
{
	AddTab(tab);
}

DockType TabDock::GetType()
{
	return DockTypes::Tab;
}

unsigned int TabDock::GetChildCount()
{
	return 0;
}

Dock* TabDock::GetDock(unsigned int index)
{
	return 0;
}

void TabDock::AddTab(Tab* tab)
{
	mTabs.push_back(tab);
	tab->SetDock(this);
}

void TabDock::RemoveTab(Tab* tab)
{
	int index = 0;
	for(; mTabs[index] != tab; index++);

	assert(index < (int)mTabs.size());

	mTabs.erase(mTabs.begin() + index);

	tab->SetDock(0);

	if(mTabs.empty())
	{
		mParent->DeleteDock(this);
	}
}

Tab* TabDock::GetCurrentTab()
{
	if(mCurrentTab < mTabs.size())
		return mTabs[mCurrentTab];
	else
		return mTabs.back();
}

Dock* TabDock::AddTabLeft(Tab* tab)
{
	return mParent->AddTabLeft(this, tab);
}

Dock* TabDock::AddTabRight(Tab* tab)
{
	return mParent->AddTabRight(this, tab);
}

Dock* TabDock::AddTabBottom(Tab* tab)
{
	return mParent->AddTabBottom(this, tab);
}

bool TabDock::OnMouseMove(int x, int y)
{
	if(mPressedTab != -1)
	{
		InitDraggedTab(x, y);
	}

	return false;
}

bool TabDock::OnLeftDown(int x, int y)
{
	if(x > GetPositionX() && x < GetPositionX() + GetWidth() &&
		y > GetPositionY() && y < GetPositionY() + CAPTION_HEIGHT)
	{
		int posX = GetPositionX();

		for(unsigned int i=0; i<mTabs.size(); i++)
		{
			if(x > posX && x < posX + GetCaptionWidth())
			{
				mCurrentTab = i;
				mPressedTab = i;
				InitDraggedTab(x, y);
				return true;
			}

			posX += GetCaptionWidth();
		}
	}

	return false;
}

bool TabDock::OnLeftUp(int x, int y)
{
	if(mPressedTab != -1)
	{
		mPressedTab = -1;
		GetRoot()->OnDrop(mDraggedTab);
		return true;
	}

	return false;
}

int TabDock::GetMinWidth()
{
	int mn = mTabs[0]->GetMinWidth();
	for(unsigned int i=1; i<mTabs.size(); i++)
	{
		int newMin = mTabs[i]->GetMinWidth();
		if(newMin > mn)
			mn = newMin;
	}
	return mn;
}

int TabDock::GetMinHeight()
{
	int mn = mTabs[0]->GetMinHeight();
	for(unsigned int i=1; i<mTabs.size(); i++)
	{
		int newMin = mTabs[i]->GetMinHeight();
		if(newMin > mn)
			mn = newMin;
	}
	return mn;
}

int TabDock::GetCaptionWidth()
{
	if(mTabs.empty())
		return 64;

	int captionWidth = GetWidth() / mTabs.size();
	
	if(captionWidth > 64)
		captionWidth = 64;
	
	return captionWidth;
}

unsigned int TabDock::GetTabCount()
{
	return mTabs.size();
}

Tab* TabDock::GetTab(unsigned int index)
{
	return mTabs[index];
}

bool TabDock::IsTabDragged()
{
	return mPressedTab != -1;
}

DraggedTab TabDock::GetDraggedTab()
{
	return mDraggedTab;
}

void TabDock::InitDraggedTab(int mouseX, int mouseY)
{
	mDraggedTab.tab = mTabs[mPressedTab];
	mDraggedTab.height = 20;
	mDraggedTab.width = GetCaptionWidth();
	mDraggedTab.x = mouseX;
	mDraggedTab.y = mouseY;
}

void TabDock::FillDropArea(DraggedTab& draggedTab)
{
	if(draggedTab.tab == GetCurrentTab() && GetTabCount() == 1)
		return;

	int x = GetPositionX();
	int y = GetPositionY();
	int width = GetWidth();
	int height = GetHeight();

	if(draggedTab.x > x && draggedTab.x < x + width && draggedTab.y > y && draggedTab.y < y + height)
	{
		if(height >= MIN_DOCK_HEIGHT*2 + SPLITTER_SIZE && draggedTab.y > y + height * 2 / 3)
		{
			draggedTab.showArea = true;
			draggedTab.areaX = x;
			draggedTab.areaY = y + height * 2 / 3;
			draggedTab.areaWidth = width;
			draggedTab.areaHeight = height - height * 2 / 3;
		} else if(draggedTab.y < y + CAPTION_HEIGHT)
		{
			if(draggedTab.tab == GetCurrentTab())
				return;
			draggedTab.showArea = true;
			draggedTab.areaX = x;
			draggedTab.areaY = y;
			draggedTab.areaWidth = width;
			draggedTab.areaHeight = CAPTION_HEIGHT;
		} else if(width >= MIN_DOCK_WIDTH*2 + SPLITTER_SIZE && draggedTab.x < x + width * 1 / 3)
		{
			draggedTab.showArea = true;
			draggedTab.areaX = x;
			draggedTab.areaY = y + CAPTION_HEIGHT;
			draggedTab.areaWidth = width * 1 / 3;
			draggedTab.areaHeight = height - CAPTION_HEIGHT;
		} else if(width >= MIN_DOCK_WIDTH*2 + SPLITTER_SIZE && draggedTab.x > x + width * 2 / 3)
		{
			draggedTab.showArea = true;
			draggedTab.areaX = x + width * 2 /3;
			draggedTab.areaY = y + CAPTION_HEIGHT;
			draggedTab.areaWidth = width - width * 2 / 3;
			draggedTab.areaHeight = height - CAPTION_HEIGHT;
		}
	}
}

bool TabDock::OnDrop(DraggedTab draggedTab)
{
	if(draggedTab.tab == GetCurrentTab() && GetTabCount() == 1)
		return false;

	int x = GetPositionX();
	int y = GetPositionY();
	int width = GetWidth();
	int height = GetHeight();

	if(draggedTab.x > x && draggedTab.x < x + width && draggedTab.y > y && draggedTab.y < y + height)
	{
		if(height >= MIN_DOCK_HEIGHT*2 + SPLITTER_SIZE && draggedTab.y > y + height * 2 / 3)
		{
			draggedTab.tab->UnDock();
			height = GetHeight();
			int size = height / 2 - SPLITTER_SIZE / 2;
			AddTabBottom(draggedTab.tab)->mSize = size;
			if(mParent->GetType() == DockTypes::Vertical)
				mSize = height - size - SPLITTER_SIZE;
			else
				mParent->mSize = height - size - SPLITTER_SIZE;
			return true;
		} else if(draggedTab.y < y + CAPTION_HEIGHT)
		{
			if(draggedTab.tab == GetCurrentTab())
				return false;
			draggedTab.tab->UnDock();
			AddTab(draggedTab.tab);

			return true;
		} else if(width >= MIN_DOCK_WIDTH*2 + SPLITTER_SIZE && draggedTab.x < x + width * 1 / 3)
		{
			draggedTab.tab->UnDock();
			width = GetWidth();
			int size = width / 2 - SPLITTER_SIZE / 2;
			AddTabLeft(draggedTab.tab)->mSize = size;
			if(mParent->GetType() == DockTypes::Vertical)
				mParent->mSize = width - size - SPLITTER_SIZE;
			else
				mSize = width - size - SPLITTER_SIZE;
			return true;
		} else if(width >= MIN_DOCK_WIDTH*2 + SPLITTER_SIZE && draggedTab.x > x + width * 2 / 3)
		{
			draggedTab.tab->UnDock();
			width = GetWidth();
			int size = width / 2 - SPLITTER_SIZE / 2;
			AddTabRight(draggedTab.tab)->mSize = size;
			if(mParent->GetType() == DockTypes::Vertical)
				mParent->mSize = width - size - SPLITTER_SIZE;
			else
				mSize = width - size - SPLITTER_SIZE;
			return true;
		}
	}

	return false;
}

void TabDock::OnResize()
{
}