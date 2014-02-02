#pragma once

class TabDock;

class Tab
{
public:
	Tab(const char* caption);

	void SetDock(TabDock* dock);
	void UnDock();

	int GetMinWidth();
	int GetMinHeight();

	const char* GetCaption();

private:
	const char* mCaption;
	TabDock* mDock;
};