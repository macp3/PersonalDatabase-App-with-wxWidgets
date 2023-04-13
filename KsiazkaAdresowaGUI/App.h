#pragma once
#include "wx/wx.h"
#include "MainFrame.h"

class myApp : public wxApp
{
public:
	virtual bool OnInit();
	MainFrame *mainFrame;
};

DECLARE_APP(myApp)
