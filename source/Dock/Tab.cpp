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