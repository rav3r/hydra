#include "TabDock.h"

#include <cassert>

TabDock::TabDock(Dock* parent, Tab* tab):
Dock(parent)
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
	return mTabs[0];
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

bool TabDock::OnEvent(const sf::Event& event)
{
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