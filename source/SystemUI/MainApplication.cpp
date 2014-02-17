#include "MainApplication.h"

#include "MainFrame.h"

#include "../Dock/RootDock.h"

RootDock* rootDock;

bool MainApplication::OnInit()
{
	// Create the main window
	MainFrame* mainFrame = new MainFrame();

	Tab* tab = new Tab("tab");
	rootDock = new RootDock(0, 0, 800, 600, tab);
	Tab* left = new Tab("left");
	(*rootDock)[0].AddTabLeft(left);
	Tab* bottom = new Tab("bottom");
	(*rootDock)[0][1].AddTabBottom(bottom);
	Tab* bottom2 = new Tab("bottom2");
	(*rootDock)[0][1].AddTabBottom(bottom2);
	Tab* left2 = new Tab("left2");
	(*rootDock)[0][1][1].AddTabLeft(left2);
	Tab* project = new Tab("project");
	(*rootDock)[0][0].AddTab(project);

	return true;
}

IMPLEMENT_APP(MainApplication);

#include <windows.h>

int main()
{
	WinMain(0,0,0,0);
}