// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".

/*
#define WXUSINGDLL
#define wxMSVC_VERSION_AUTO

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/glcanvas.h>

#include "wxSFMLCanvas.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/OpenGL.hpp>

#include "Dock/DebugDraw.h"
#include <iostream>

RootDock* rootDock;
class MyCanvas : public wxSFMLCanvas
{
public :

	DECLARE_EVENT_TABLE()
public:
    MyCanvas(wxWindow*  Parent,
             wxWindowID Id,
             wxPoint&   Position,
             wxSize&    Size,
             long       Style = 0) :
    wxSFMLCanvas(Parent, Id, Position, Size, Style)
    {
			gDebugFont.loadFromFile("data/SourceSansPro.otf");
    }


    virtual void OnUpdate()
    {



        // Clear the view

		Dock_DebugDraw(*rootDock, *this, rootDock->GetWidth(), rootDock->GetHeight());

		glFlush();
		
    }

	bool activate(bool)
	{
		
		return true;
	}

		sf::Vector2u getSize() const { return sf::Vector2u(GetSize().x, GetSize().y); }

		
	virtual void OnResize(int width, int height)
	{
		this->GetParent()->SetMinClientSize(wxSize(rootDock->GetMinWidth(), rootDock->GetMinHeight()));

		rootDock->SetWidth(width);
		rootDock->SetHeight(height);
		rootDock->OnResize();
	}

    void OnIdle(wxIdleEvent&)
	{
	}

	void OnSize(wxSizeEvent& s)
	{
		OnResize(s.GetSize().x, s.GetSize().y);
	}

    void OnEraseBackground(wxEraseEvent&)
	{
	}
};

BEGIN_EVENT_TABLE(MyCanvas, wxSFMLCanvas)
    EVT_IDLE(MyCanvas::OnIdle)
	EVT_SIZE(MyCanvas::OnSize)
	EVT_SIZING(MyCanvas::OnSize)
    EVT_PAINT(MyCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(MyCanvas::OnEraseBackground)
END_EVENT_TABLE()

class MyFrame : public wxFrame
{
public :

    MyFrame() :
    wxFrame(NULL, wxID_ANY, "SFML wxWidgets", wxDefaultPosition, wxSize(800, 600), wxFULL_REPAINT_ON_RESIZE | wxDEFAULT_FRAME_STYLE )
    {
		Show();

		new MyCanvas(this, wxID_ANY, wxPoint(0, 0), wxSize(800, 600));
    }
};


class MyApplication : public wxApp
{
private :

    virtual bool OnInit()
    {
		Tab* tab = new Tab("tab");
		rootDock = new RootDock(0, 0, 800, 600, tab);
        // Create the main window
        MyFrame* MainFrame = new MyFrame;


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
};

IMPLEMENT_APP(MyApplication);

#include <windows.h>

int main()
{
	WinMain(0,0,0,0);
}*/