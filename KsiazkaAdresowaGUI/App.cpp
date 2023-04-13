#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(myApp);

bool myApp::OnInit()
{
    mainFrame = new MainFrame("Ksiazka adresowa z GUI");
    mainFrame->SetClientSize(1500, 700);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}


