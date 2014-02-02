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
	return 128;
}

int Tab::GetMinHeight()
{
	return 128;
}

const char* Tab::GetCaption()
{
	return mCaption;
}