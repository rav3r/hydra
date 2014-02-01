#pragma once

class TabDock;

class Tab
{
public:
	Tab(const char* caption);

	void SetDock(TabDock* dock);
	void UnDock();

private:
	const char* mCaption;
	TabDock* mDock;
};