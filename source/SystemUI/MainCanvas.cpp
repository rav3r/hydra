#include "MainCanvas.h"

#include "../Dock/RootDock.h"
#include "../Dock/DebugDraw.h"

extern RootDock* rootDock;

sf::Texture texture;
sf::Sprite sprite;

wxBEGIN_EVENT_TABLE(MainCanvas, wxSFMLCanvas)
	EVT_MOTION(MainCanvas::OnMotion)
	EVT_LEFT_DOWN(MainCanvas::OnLeftDown)
	EVT_LEFT_UP(MainCanvas::OnLeftUp)
	EVT_MOUSE_CAPTURE_LOST(MainCanvas::OnCaptureLost)
wxEND_EVENT_TABLE()


MainCanvas::MainCanvas(wxWindow* parent, wxWindowID id, wxPoint& pos, wxSize& size, long style):
wxSFMLCanvas(parent, id, pos, size, style)
{
	texture.loadFromFile("data/img.jpg");
	gDebugFont.loadFromFile("data/SourceSansPro.otf");
}

void MainCanvas::OnUpdate()
{
	clear();

	Dock_DebugDraw(*rootDock, *this, rootDock->GetWidth(), rootDock->GetHeight());
}

void MainCanvas::OnResize(int width, int height)
{
	this->GetParent()->SetMinClientSize(wxSize(rootDock->GetMinWidth(), rootDock->GetMinHeight()));

	rootDock->SetWidth(width);
	rootDock->SetHeight(height);
	rootDock->OnResize();
}

void MainCanvas::OnMotion(wxMouseEvent& event)
{
	rootDock->OnMouseMove(event.GetX(), event.GetY());
}

void MainCanvas::OnLeftDown(wxMouseEvent& event)
{
	CaptureMouse();

	rootDock->OnLeftDown(event.GetX(), event.GetY());
}

void MainCanvas::OnLeftUp(wxMouseEvent& event)
{
	ReleaseCapture();

	rootDock->OnLeftUp(event.GetX(), event.GetY());
}

void MainCanvas::OnCaptureLost(wxMouseCaptureLostEvent&)
{
	// todo
}