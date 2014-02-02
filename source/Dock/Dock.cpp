#include "Dock.h"

#include <cassert>

Dock::Dock(Dock* parent): mParent(parent), mSize(128)
{
}

Dock& Dock::operator[](unsigned int index)
{
	return *GetDock(index);
}

void Dock::DeleteDock(Dock* dock)
{
	assert(!"unimplemented");
}

void Dock::Simplify(Dock* oldChild, Dock* newChild)
{
	assert(!"unimplemented");
}

Dock* Dock::AddTabLeft(Tab* tab)
{
	assert(!"unimplemented");
	return 0;
}

Dock* Dock::AddTabLeft(Dock* where, Tab* tab)
{
	assert(!"unimplemented");
	return 0;
}

Dock* Dock::AddTabRight(Tab* tab)
{
	assert(!"unimplemented");
	return 0;
}

Dock* Dock::AddTabRight(Dock* where, Tab* tab)
{
	assert(!"unimplemented");
	return 0;
}

Dock* Dock::AddTabBottom(Tab* tab)
{
	assert(!"unimplemented");
	return 0;
}

Dock* Dock::AddTabBottom(Dock* where, Tab* tab)
{
	assert(!"unimplemented");
	return 0;
}

void Dock::AddTab(Tab* tab)
{
	assert(!"unimplemented");
}

void Dock::RemoveTab(Tab* tab)
{
	assert(!"unimplemented");
}

Tab* Dock::GetCurrentTab()
{
	return 0;
}

int Dock::GetPositionX()
{
	return mParent->ComputeChildPositionX(this);
}

int Dock::GetPositionY()
{
	return mParent->ComputeChildPositionY(this);
}

int Dock::GetWidth()
{
	return mParent->ComputeChildWidth(this);
}

int Dock::GetHeight()
{
	return mParent->ComputeChildHeight(this);
}

int Dock::ComputeChildPositionX(Dock* dock)
{
	assert(!"unimplemented");
	return 0;
}

int Dock::ComputeChildPositionY(Dock* dock)
{
	assert(!"unimplemented");
	return 0;
}

int Dock::ComputeChildWidth(Dock* dock)
{
	assert(!"unimplemented");
	return 0;
}

int Dock::ComputeChildHeight(Dock* dock)
{
	assert(!"unimplemented");
	return 0;
}

Dock* Dock::GetRoot()
{
	if(mParent)
		return mParent->GetRoot();
	return this;
}