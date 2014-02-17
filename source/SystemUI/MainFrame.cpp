#include "MainFrame.h"

#include "MainCanvas.h"

MainFrame::MainFrame():
wxFrame(NULL, wxID_ANY, "hydra", wxDefaultPosition, wxSize(800, 600), wxFULL_REPAINT_ON_RESIZE|wxDEFAULT_FRAME_STYLE)
{
	Show();
	new MainCanvas(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 600));
}