#pragma once

#include <SFML/Graphics.hpp>
#include <wx/wx.h>
#include <wx/glcanvas.h>

class wxSFMLCanvas : public wxGLCanvas, public sf::RenderTarget
{
public:
	wxSFMLCanvas(wxWindow* parent=0, wxWindowID id=-1, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=0);
	virtual ~wxSFMLCanvas();

private:
	DECLARE_EVENT_TABLE()

	virtual void OnUpdate() = 0;
	virtual void OnResize(int width, int height) = 0;

	// Events
	void OnIdle(wxIdleEvent&);
	void OnSize(wxSizeEvent&);
	void OnPaint(wxPaintEvent&);
	void OnEraseBackground(wxEraseEvent&);

	// wxControl
	wxSize DoGetBestSize() const;

	// sf::RenderTarget
	bool activate(bool);
	sf::Vector2u getSize() const;
};
