#include "HorizontalDock.h"

#include "TabDock.h"
#include "VerticalDock.h"
#include "Sizes.h"

#include <cassert>

HorizontalDock::HorizontalDock(Dock* parent, Dock* firstChild):
Dock(parent), mPressedSplitter(-1)
{
	mDocks.push_back(firstChild);
	firstChild->mParent = this;
}

DockType HorizontalDock::GetType()
{
	return DockTypes::Horizontal;
}

unsigned int HorizontalDock::GetChildCount()
{
	return mDocks.size();
}

Dock* HorizontalDock::GetDock(unsigned int index)
{
	return mDocks[index];
}

void HorizontalDock::DeleteDock(Dock* dock)
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

void HorizontalDock::Simplify(Dock* oldChild, Dock* newChild)
{
	int index = 0;
	for(; mDocks[index] != oldChild; index++);

	delete mDocks[index];
	mDocks[index] = newChild;
	mDocks[index]->mParent = this;
}

Dock* HorizontalDock::AddTabLeft(Tab* tab)
{
	TabDock* tabDock = new TabDock(this, tab);
	mDocks.insert(mDocks.begin(), tabDock);
	
	return tabDock;
}

Dock* HorizontalDock::AddTabLeft(Dock* where, Tab* tab)
{
	int index = 0;
	for(; mDocks[index] != where; index++);

	assert(index < (int)mDocks.size());

	mDocks.insert(mDocks.begin() + index, new TabDock(this, tab));

	return mDocks[index];
}

Dock* HorizontalDock::AddTabRight(Tab* tab)
{
	TabDock* tabDock = new TabDock(this, tab);
	mDocks.push_back(tabDock);
	
	return tabDock;
}

Dock* HorizontalDock::AddTabRight(Dock* where, Tab* tab)
{
	int index = 0;
	for(; mDocks[index] != where; index++);

	assert(index < (int)mDocks.size());

	mDocks.insert(mDocks.begin() + index + 1, new TabDock(this, tab));

	return mDocks[index + 1];
}

Dock* HorizontalDock::AddTabBottom(Tab* tab)
{
	return mParent->AddTabBottom(this, tab);
}

Dock* HorizontalDock::AddTabBottom(Dock* where, Tab* tab)
{
	int index = 0;
	for(; mDocks[index] != where; index++);

	Dock* tmp = mDocks[index];
	mDocks[index] = new VerticalDock(this, tmp);
	return mDocks[index]->AddTabBottom(tab);
}

int HorizontalDock::ComputeChildPositionX(Dock* dock)
{
	int index = 0;
	int pos = GetPositionX();
	for(; mDocks[index] != dock; index++)
	{
		pos += mDocks[index]->mSize;
		pos += SPLITTER_SIZE;
	}

	return pos;
}

int HorizontalDock::ComputeChildPositionY(Dock* dock)
{
	return GetPositionY();
}

int HorizontalDock::ComputeChildWidth(Dock* dock)
{
	if(dock != mDocks.back())
		return dock->mSize;

	return GetWidth() - ComputeChildPositionX(dock) + GetPositionX();
}

int HorizontalDock::ComputeChildHeight(Dock* dock)
{
	return GetHeight();
}

bool HorizontalDock::OnEvent(const sf::Event& event)
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		if(mDocks[i]->OnEvent(event))
			return true;

	if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		mPressedSplitter = -1;
		if(event.mouseButton.y > GetPositionY() && event.mouseButton.y < GetPositionY() + GetHeight())
		{
			int currentX = GetPositionX();
			for(int i=0; i<(int)mDocks.size()-1; i++)
			{
				currentX += mDocks[i]->mSize;
				if(event.mouseButton.x > currentX && event.mouseButton.x < currentX + SPLITTER_SIZE)
				{
					mPressedSplitter = i;
					mPressedSplitterDiff = event.mouseButton.x - currentX;
					break;
				}
				currentX += SPLITTER_SIZE;
			}
		}
	} else if(event.type == sf::Event::MouseLeft || (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
	{
		mPressedSplitter = -1;
	} else if(event.type == sf::Event::MouseMoved)
	{
		if(mPressedSplitter != -1)
		{
			int diff = event.mouseMove.x - mDocks[mPressedSplitter]->GetPositionX() - mDocks[mPressedSplitter]->mSize - mPressedSplitterDiff;
			ChangeDockSizes(diff);
		}
	}

	return false;
}

void HorizontalDock::ChangeDockSizes(int diff)
{
	if(diff < 0)
	{
		// splitter -> 0
		int taken = 0;
		diff = -diff;
		for(int i=mPressedSplitter; i>=0 && taken != diff; i--)
		{
			int canTake = mDocks[i]->mSize - mDocks[i]->GetMinWidth();
			if(diff - taken > canTake)
			{
				mDocks[i]->mSize -= canTake;
				taken += canTake;
			} else
			{
				mDocks[i]->mSize -= diff - taken;
				taken = diff;
			}
		}
		mDocks[mPressedSplitter+1]->mSize += taken;
	} else
	{
		// splitter -> mDocks.size() - 1
		int taken = 0;
		for(int i=mPressedSplitter+1; i<(int)mDocks.size() && taken != diff; i++)
		{
			int canTake = mDocks[i]->GetWidth() - mDocks[i]->GetMinWidth();
			if(diff - taken > canTake)
			{
				mDocks[mPressedSplitter]->mSize += canTake;
				mDocks[i]->mSize -= canTake;
				taken += canTake;
			} else
			{
				mDocks[mPressedSplitter]->mSize += diff - taken;
				mDocks[i]->mSize -= diff - taken;
				taken = diff;
			}
		}
	}
}

int HorizontalDock::GetMinWidth()
{
	int mn = mDocks[0]->GetMinWidth();
	for(unsigned int i=1; i<mDocks.size(); i++)
	{
		mn += SPLITTER_SIZE;
		mn += mDocks[i]->GetMinWidth();
	}
	return mn;
}

int HorizontalDock::GetMinHeight()
{
	int mn = mDocks[0]->GetMinHeight();
	for(unsigned int i=1; i<mDocks.size(); i++)
	{
		int newMin = mDocks[i]->GetMinHeight();
		if(newMin > mn)
			mn = newMin;
	}
	return mn;
}

bool HorizontalDock::IsTabDragged()
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		if(mDocks[i]->IsTabDragged())
			return true;
	return false;
}

DraggedTab HorizontalDock::GetDraggedTab()
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		if(mDocks[i]->IsTabDragged())
			return mDocks[i]->GetDraggedTab();
	return DraggedTab();
}

void HorizontalDock::FillDropArea(DraggedTab& draggedTab)
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		mDocks[i]->FillDropArea(draggedTab);
}

bool HorizontalDock::OnDrop(DraggedTab draggedTab)
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		if(mDocks[i]->OnDrop(draggedTab))
			return true;
	return false;
}