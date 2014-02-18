#include "RootDock.h"

#include "TabDock.h"
#include "HorizontalDock.h"
#include "VerticalDock.h"

#include <cassert>

RootDock::RootDock(int x, int y, int width, int height, Tab* tab):
Dock(0), mX(x), mY(y), mWidth(width), mHeight(height), mRootDock(0)
{
	mRootDock = new TabDock(this, tab);
}

DockType RootDock::GetType()
{
	return DockTypes::Root;
}

unsigned int RootDock::GetChildCount()
{
	return 1;
}

Dock* RootDock::GetDock(unsigned int index)
{
	return mRootDock;
}

void RootDock::Simplify(Dock* oldChild, Dock* newChild)
{
	assert(oldChild == mRootDock);

	delete mRootDock;
	mRootDock = newChild;
	mRootDock->mParent = this;
}

Dock* RootDock::AddTabLeft(Dock* where, Tab* tab)
{
	Dock* tmp = mRootDock;
	mRootDock = new HorizontalDock(this, tmp);
	return mRootDock->AddTabLeft(tab);
}

Dock* RootDock::AddTabRight(Dock* where, Tab* tab)
{
	Dock* tmp = mRootDock;
	mRootDock = new HorizontalDock(this, tmp);
	return mRootDock->AddTabRight(tab);
}

Dock* RootDock::AddTabBottom(Dock* where, Tab* tab)
{
	Dock* tmp = mRootDock;
	mRootDock = new VerticalDock(this, tmp);
	return mRootDock->AddTabBottom(tab);
}

int RootDock::GetPositionX()
{
	return mX;
}

int RootDock::GetPositionY()
{
	return mY;
}

int RootDock::GetWidth()
{
	return mWidth;
}

int RootDock::GetHeight()
{
	return mHeight;
}

int RootDock::ComputeChildPositionX(Dock* dock)
{
	assert(dock == mRootDock);

	return GetPositionX();
}

int RootDock::ComputeChildPositionY(Dock* dock)
{
	assert(dock == mRootDock);

	return GetPositionY();
}

int RootDock::ComputeChildWidth(Dock* dock)
{
	assert(dock == mRootDock);

	return GetWidth();
}

int RootDock::ComputeChildHeight(Dock* dock)
{
	assert(dock == mRootDock);

	return GetHeight();
}

void RootDock::SetWidth(int width)
{
	mWidth = width;
}

void RootDock::SetHeight(int height)
{
	mHeight = height;
}

bool RootDock::OnMouseMove(int x, int y)
{
	return mRootDock->OnMouseMove(x, y);
}

bool RootDock::OnLeftDown(int x, int y)
{
	return mRootDock->OnLeftDown(x, y);
}

bool RootDock::OnLeftUp(int x, int y)
{
	return mRootDock->OnLeftUp(x, y);
}

int RootDock::GetMinWidth()
{
	return mRootDock->GetMinWidth();
}

int RootDock::GetMinHeight()
{
	return mRootDock->GetMinHeight();
}

bool RootDock::IsTabDragged()
{
	return mRootDock->IsTabDragged();
}

DraggedTab RootDock::GetDraggedTab()
{
	return mRootDock->GetDraggedTab();
}

void RootDock::FillDropArea(DraggedTab& draggedTab)
{
	mRootDock->FillDropArea(draggedTab);
}

bool RootDock::OnDrop(DraggedTab draggedTab)
{
	return mRootDock->OnDrop(draggedTab);
}

void RootDock::OnResize()
{
	mRootDock->OnResize();
}