#pragma once

#include "wxSFMLCanvas.h"

class MainCanvas: public wxSFMLCanvas
{
public:
	MainCanvas(wxWindow* parent, wxWindowID id, wxPoint& pos, wxSize& size, long style = 0);

	virtual void OnUpdate();
	virtual void OnResize(int width, int height);
};
