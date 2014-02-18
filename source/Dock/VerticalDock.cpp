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

	int addictionalSize = mDocks[index]->GetHeight() + SPLITTER_SIZE;
	delete mDocks[index];
	mDocks.erase(mDocks.begin() + index);

	if(index == 0)
		mDocks[0]->mSize += addictionalSize;
	else
		mDocks[index-1]->mSize += addictionalSize;

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

	int oldHeight = oldChild->GetHeight();
	DockType oldType = oldChild->GetType();

	delete mDocks[index];
	mDocks[index] = newChild;
	mDocks[index]->mParent = this;

	mDocks[index]->mSize = oldHeight;
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
	int oldSize = mDocks[index]->mSize;
	mDocks[index] = new HorizontalDock(this, tmp);
	mDocks[index]->mSize = oldSize;
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
	int oldSize = mDocks[index]->mSize;
	mDocks[index] = new HorizontalDock(this, tmp);
	mDocks[index]->mSize = oldSize;
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

bool VerticalDock::OnMouseMove(int x, int y)
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		if(mDocks[i]->OnMouseMove(x, y))
			return true;

	if(mPressedSplitter != -1)
	{
		int diff = y - mDocks[mPressedSplitter]->GetPositionY() - mDocks[mPressedSplitter]->mSize - mPressedSplitterDiff;
		ChangeDockSizes(diff);
	}

	return false;
}

bool VerticalDock::OnLeftDown(int x, int y)
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		if(mDocks[i]->OnLeftDown(x, y))
			return true;

	mPressedSplitter = -1;
	if(x > GetPositionX() && x < GetPositionX() + GetWidth())
	{
		int currentY = GetPositionY();
		for(int i=0; i<(int)mDocks.size()-1; i++)
		{
			currentY += mDocks[i]->mSize;
			if(y > currentY && y < currentY + SPLITTER_SIZE)
			{
				mPressedSplitter = i;
				mPressedSplitterDiff = y - currentY;
				break;
			}
			currentY += SPLITTER_SIZE;
		}
	}

	return false;
}

bool VerticalDock::OnLeftUp(int x, int y)
{
	for(unsigned int i=0; i<mDocks.size(); i++)
		if(mDocks[i]->OnLeftUp(x, y))
			return true;

	mPressedSplitter = -1;

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
			int canTake = (mDocks[i]->GetHeight()) - mDocks[i]->GetMinHeight();
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

	for(unsigned int i=0; i<mDocks.size(); i++)
		mDocks[i]->OnResize();
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

void VerticalDock::OnResize()
{
	int height = GetHeight();
	int diff = height - (mDocks.back()->GetPositionY() - GetPositionY() + mDocks.back()->GetMinHeight());

	if(diff < 0)
	{
		int taken = 0;
		diff = -diff;
		for(int i=(int)mDocks.size()-2; i>=0 && diff!=taken; i--)
		{
			int canTake = (mDocks[i]->GetHeight()) - mDocks[i]->GetMinHeight();
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
	}

	for(unsigned int i=0; i<mDocks.size(); i++)
		mDocks[i]->OnResize();
}