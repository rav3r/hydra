#include "Tab.h"

#include "TabDock.h"
#include "Sizes.h"

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
	return MIN_DOCK_WIDTH;
}

int Tab::GetMinHeight()
{
	return MIN_DOCK_HEIGHT;
}

const char* Tab::GetCaption()
{
	return mCaption;
}