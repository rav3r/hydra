#include "VerticalDock.h"

#include "HorizontalDock.h"
#include "TabDock.h"
#include "Sizes.h"

#include <cassert>

VerticalDock::VerticalDock(Dock* parent, Dock* firstChild):
Dock(parent), mPressedSplitter(-1)
{
	mDocks.push_back(firstChild);
	firstChild->mParent = this;
}

DockType VerticalDock::GetType()
{
	return DockTypes::Vertical;
}

unsigned int VerticalDock::GetChildCount()
{
	return mDocks.size();
}

Dock* VerticalDock::GetDock(unsigned int index)
{
	return mDocks[index];
}

void VerticalDock::DeleteDock(Dock* dock)
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

void VerticalDock::Simplify(Dock* oldChild, Dock* newChild)
{
	int index = 0;
	for(; mDocks[index] != oldChild; index++);

	delete mDocks[index];
	mDocks[index] = newChild;
	mDocks[index]->mParent = this;
}

Dock* VerticalDock::AddTabLeft(Tab* tab)
{
	return mParent->AddTabLeft(this, tab);
}

Dock* VerticalDock::AddTabLeft(Dock* where, Tab* tab)
{
	int index = 0;
	for(; mDocks[index] != where; index++);

	Dock* tmp = mDocks[index];
	mDocks[index] = new HorizontalDock(this, tmp);
	return mDocks[index]->AddTabLeft(tab);
}

Dock* VerticalDock::AddTabRight(Tab* tab)
{
	return mParent->AddTabRight(this, tab);
}

Dock* VerticalDock::AddTabRight(Dock* where, Tab* tab)
{
	int index = 0;
	for(; mDocks[index] != where; index++);

	Dock* tmp = mDocks[index];
	mDocks[index] = new HorizontalDock(this, tmp);
	return mDocks[index]->AddTabRight(tab);
}

Dock* VerticalDock::AddTabBottom(Tab* tab)
{
	TabDock* tabDock = new TabDock(this, tab);
	mDocks.push_back(tabDock);
	
	return tabDock;
}

Dock* VerticalDock::AddTabBottom(Dock* where, Tab* tab)
{
	int index = 0;
	for(; mDocks[index] != where; index++);

	assert(index < (int)mDocks.size());

	if(index == (int)(mDocks.size())-1)
		mDocks.push_back(new TabDock(this, tab));
	else
		mDocks.insert(mDocks.begin() + index + 1, new TabDock(this, tab));

	return mDocks[index + 1];
}

int VerticalDock::ComputeChildPositionX(Dock* dock)
{
	return GetPositionX();
}

int VerticalDock::ComputeChildPositionY(Dock* dock)
{
	int index = 0;
	int pos = GetPositionY();
	for(; mDocks[index] != dock; index++)
	{
		pos += mDocks[index]->mSize;
		pos += SPLITTER_SIZE;
	}

	return pos;
}

int VerticalDock::ComputeChildWidth(Dock* dock)
{
	return GetWidth();
}

int VerticalDock::ComputeChildHeight(Dock* dock)
{
	if(dock != mDocks.back())
		return dock->mSize;

	return GetHeight() - ComputeChildPositionY(dock) + GetPositionY();
}

bool VerticalDock::OnEvent(const sf::Event& event)
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		if(mDocks[i]->OnEvent(event))
			return true;

	if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		mPressedSplitter = -1;
		if(event.mouseButton.x > GetPositionX() && event.mouseButton.x < GetPositionX() + GetWidth())
		{
			int currentY = GetPositionY();
			for(int i=0; i<(int)mDocks.size()-1; i++)
			{
				currentY += mDocks[i]->mSize;
				if(event.mouseButton.y > currentY && event.mouseButton.y < currentY + SPLITTER_SIZE)
				{
					mPressedSplitter = i;
					mPressedSplitterDiff = event.mouseButton.y - currentY;
					break;
				}
				currentY += SPLITTER_SIZE;
			}
		}
	} else if(event.type == sf::Event::MouseLeft || (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left))
	{
		mPressedSplitter = -1;
	} else if(event.type == sf::Event::MouseMoved)
	{
		if(mPressedSplitter != -1)
		{
			int diff = event.mouseMove.y - mDocks[mPressedSplitter]->GetPositionY() - mDocks[mPressedSplitter]->mSize - mPressedSplitterDiff;
			ChangeDockSizes(diff);
		}
	}

	return false;
}

void VerticalDock::ChangeDockSizes(int diff)
{
	if(diff < 0)
	{
		// splitter -> 0
		int taken = 0;
		diff = -diff;
		for(int i=mPressedSplitter; i>=0 && taken != diff; i--)
		{
			int canTake = mDocks[i]->mSize - mDocks[i]->GetMinHeight();
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
			int canTake = mDocks[i]->GetHeight() - mDocks[i]->GetMinHeight();
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
		mDocks[mPressedSplitter]->mSize += taken;
	}
}

int VerticalDock::GetMinWidth()
{
	int mn = mDocks[0]->GetMinWidth();
	for(unsigned int i=1; i<mDocks.size(); i++)
	{
		int newMin = mDocks[i]->GetMinWidth();
		if(newMin > mn)
			mn = newMin;
	}
	return mn;
}

int VerticalDock::GetMinHeight()
{
	int mn = mDocks[0]->GetMinHeight();
	for(unsigned int i=1; i<mDocks.size(); i++)
	{
		mn += SPLITTER_SIZE;
		mn += mDocks[i]->GetMinHeight();
	}
	return mn;
}

bool VerticalDock::IsTabDragged()
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		if(mDocks[i]->IsTabDragged())
			return true;
	return false;
}

DraggedTab VerticalDock::GetDraggedTab()
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		if(mDocks[i]->IsTabDragged())
			return mDocks[i]->GetDraggedTab();
	return DraggedTab();
}

void VerticalDock::FillDropArea(DraggedTab& draggedTab)
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		mDocks[i]->FillDropArea(draggedTab);
}

bool VerticalDock::OnDrop(DraggedTab draggedTab)
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		if(mDocks[i]->OnDrop(draggedTab))
			return true;
	return false;
}