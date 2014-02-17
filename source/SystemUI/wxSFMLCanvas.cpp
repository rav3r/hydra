#include "wxSFMLCanvas.h"

BEGIN_EVENT_TABLE(wxSFMLCanvas, wxControl)
	EVT_IDLE(wxSFMLCanvas::OnIdle)
	EVT_SIZE(wxSFMLCanvas::OnSize)
	EVT_SIZING(wxSFMLCanvas::OnSize)
	EVT_PAINT(wxSFMLCanvas::OnPaint)
	EVT_ERASE_BACKGROUND(wxSFMLCanvas::OnEraseBackground)
END_EVENT_TABLE()


wxSFMLCanvas::wxSFMLCanvas(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style):
wxGLCanvas(parent, id, pos, size, style)
{
	wxGLCanvas::SetCurrent();
	initialize();
}

wxSFMLCanvas::~wxSFMLCanvas()
{
}

void wxSFMLCanvas::OnIdle(wxIdleEvent &)
{
	Refresh();
}

void wxSFMLCanvas::OnPaint(wxPaintEvent &)
{
	SetCurrent();
	wxPaintDC Dc(this);

	OnUpdate();

	glFlush();
	SwapBuffers();
}

void wxSFMLCanvas::OnEraseBackground(wxEraseEvent &)
{
	// Don't do anything. We intercept this event in order to prevent the
	// parent class to draw the background before repainting the window,
	// which would cause some flickering
}

wxSize wxSFMLCanvas::DoGetBestSize() const
{
	return this->GetSize();
}

void wxSFMLCanvas::OnSize(wxSizeEvent& s)
{
	OnResize(s.GetSize().x, s.GetSize().y);
	Refresh();
}

bool wxSFMLCanvas::activate(bool)
{
	SetCurrent();
	return true;
}

sf::Vector2u wxSFMLCanvas::getSize() const
{
	return sf::Vector2u(GetSize().x, GetSize().y);
}