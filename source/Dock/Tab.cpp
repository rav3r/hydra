#include "Tab.h"

#include "TabDock.h"

Tab::Tab(const char* caption): mCaption(caption)
{
}

void Tab::SetDock(TabDock* dock)
{
	mDock = dock;
}

void Tab::UnDock()
{
	mDock->RemoveTab(this);
}

int Tab::GetMinWidth()
{
	return 64;
}

int Tab::GetMinHeight()
{
	return 64;
}

const char* Tab::GetCaption()
{
	return mCaption;
}