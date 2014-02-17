#include "MainCanvas.h"

#include "../Dock/RootDock.h"
#include "../Dock/DebugDraw.h"

extern RootDock* rootDock;

sf::Texture texture;
sf::Sprite sprite;

MainCanvas::MainCanvas(wxWindow* parent, wxWindowID id, wxPoint& pos, wxSize& size, long style):
wxSFMLCanvas(parent, id, pos, size, style)
{
	texture.loadFromFile("data/img.jpg");
	gDebugFont.loadFromFile("data/SourceSansPro.otf");
}

void MainCanvas::OnUpdate()
{
	Dock_DebugDraw(*rootDock, *this, rootDock->GetWidth(), rootDock->GetHeight());
}

void MainCanvas::OnResize(int width, int height)
{
	this->GetParent()->SetMinClientSize(wxSize(rootDock->GetMinWidth(), rootDock->GetMinHeight()));

	rootDock->SetWidth(width);
	rootDock->SetHeight(height);
	rootDock->OnResize();
}
