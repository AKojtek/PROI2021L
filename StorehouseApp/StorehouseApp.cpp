#include "MainFrame.h"
#include "ExtraFrame.h"

class MainApp : public wxApp
{
public:
    Storehouse sh;
    virtual bool OnInit();
};

IMPLEMENT_APP(MainApp);

bool MainApp::OnInit()
{
    EntryFrame* entry_frame = new EntryFrame();
    entry_frame->Show(true);

    return true;
}
