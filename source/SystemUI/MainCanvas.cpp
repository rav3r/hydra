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

	mCursorChanged = false;
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

	if(mCursorChanged == false)
	{
		static wxCursor normal(wxCURSOR_ARROW);
		static wxCursor sizeNS(wxCURSOR_SIZENS);
		static wxCursor sizeWE(wxCURSOR_SIZEWE);

		switch(rootDock->GetCursorStyle(event.GetX(), event.GetY()))
		{
		case CursorStyles::SIZE_NS:
			SetCursor(sizeNS);
			break;
		case CursorStyles::SIZE_WE:
			SetCursor(sizeWE);
			break;
		default:
			SetCursor(normal);
			break;
		}
	}
}

void MainCanvas::OnLeftDown(wxMouseEvent& event)
{
	CaptureMouse();

	if(rootDock->OnLeftDown(event.GetX(), event.GetY()))
		mCursorChanged = true;
}

void MainCanvas::OnLeftUp(wxMouseEvent& event)
{
	ReleaseCapture();

	rootDock->OnLeftUp(event.GetX(), event.GetY());

	mCursorChanged = false;
}

void MainCanvas::OnCaptureLost(wxMouseCaptureLostEvent&)
{
	// todo
}