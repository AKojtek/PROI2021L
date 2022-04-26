#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/numdlg.h>

#include "Storehouse.h"

class MainFrame : public wxFrame
{
public:
    int drawing_width, drawing_length;
    std::vector<wxButton*> product_buttons;
    
    wxTextCtrl* sh_details_txt;

    void OnSave(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnExit(wxCloseEvent& event);

    void OnRearrange(wxCommandEvent& event);
    void OnGetReceipt(wxCommandEvent& event);

    void OnNewClient(wxCommandEvent& event);
    void OnNewProduct(wxCommandEvent& event);
    void OnRemClient(wxCommandEvent& event);
    void OnRemProduct(wxCommandEvent& event);

public:
    Storehouse* sh;

    MainFrame(Storehouse* m_sh);

    void Update();
    void UpdateDrawing();
};

enum
{
    ID_Save = wxID_HIGHEST + 1,
    ID_Open = wxID_HIGHEST + 2,
    ID_NewClient = wxID_HIGHEST + 3,
    ID_NewProduct = wxID_HIGHEST + 4,
    ID_RemClient = wxID_HIGHEST + 5,
    ID_RemProduct = wxID_HIGHEST + 6,
    BUTTON_Rearrange = wxID_HIGHEST + 7,
    BUTTON_GetReceipt = wxID_HIGHEST + 8,
    BUTTON_NewCli = wxID_HIGHEST + 9,
    BUTTON_RemCli = wxID_HIGHEST + 10,
    BUTTON_NewProd = wxID_HIGHEST + 11,
    BUTTON_RemProd = wxID_HIGHEST + 12
};
