#include "Dock.h"

#include <cassert>

Dock::Dock(Dock* parent): mParent(parent)
{
}

Dock& Dock::operator[](unsigned int index)
{
	return *GetDock(index);
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

Tab* Dock::GetCurrentTab()
{
	return 0;
}