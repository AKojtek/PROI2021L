#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/spinctrl.h>
#include <wx/datectrl.h>

#include "Storehouse.h"
#include "MainFrame.h"

class ExtraFrame : public wxFrame
{
protected:
    MainFrame* parent;
public:
    ExtraFrame(std::string name = "", MainFrame* m_parent = NULL);
    wxButton* cancel_button;
    wxButton* ok_button;

    void OnOK(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
};


class EntryFrame : public ExtraFrame
{
public:
    wxTextCtrl* sh_name_edit;
    wxSpinCtrl* sh_width_edit;
    wxSpinCtrl* sh_length_edit;

    EntryFrame();

    void OnOK(wxCommandEvent& event);
    void OnNewSH(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
};

class NewStorehouseFrame : public ExtraFrame
{
public:
    wxTextCtrl* sh_name_edit;
    wxSpinCtrl* sh_width_edit;
    wxSpinCtrl* sh_length_edit;
    wxSpinCtrl* shortterm_time_edit;
    wxSpinCtrl* penalty_mult_edit;
    wxSpinCtrl* longterm_cost_edit;
    wxSpinCtrl* shortterm_cost_edit;
    wxSpinCtrl* exclusive_cost_edit;
    wxSpinCtrl* wholesale_cost_edit;

    NewStorehouseFrame();

    void OnOK(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
};


class NewClientFrame : public ExtraFrame
{
public:
    wxTextCtrl* cli_name_edit;
    wxTextCtrl* cli_city_edit;
    wxTextCtrl* cli_phone_edit;

    NewClientFrame(MainFrame* m_parent);

    void OnOK(wxCommandEvent& event);
};


class NewProductFrame : public ExtraFrame
{
public:
    wxSpinCtrl* prod_owner_id_edit;
    wxTextCtrl* prod_name_edit;
    wxSpinCtrl* prod_width_edit;
    wxSpinCtrl* prod_height_edit;
    wxChoice* prod_type_choice;

    wxDatePickerCtrl* prod_begin_edit = nullptr;
    wxDatePickerCtrl* prod_end_edit = nullptr;
    wxTextCtrl* prod_password_edit = nullptr;

    NewProductFrame(MainFrame* m_parent);

    void OnOK(wxCommandEvent& event);
    void OnChoice(wxCommandEvent& event);

    void addButtonToDrawing(int id);
};


class GetReceiptFrame : public ExtraFrame
{
public:
    wxSpinCtrl* client_id_edit;
    wxTextCtrl* prods_left_txt;
    wxTextCtrl* prods_chosen_txt;
    wxSpinCtrl* prod_add_edit;
    wxSpinCtrl* prod_rem_edit;

    GetReceiptFrame(MainFrame* m_parent);

    void OnCliIdOK(wxCommandEvent& event);
    void OnProdAddOK(wxCommandEvent& event);
    void OnProdRemOK(wxCommandEvent& event);
    void OnOK(wxCommandEvent& event);
};


enum
{
    BUTTON_Cancel = wxID_HIGHEST + 1,
    BUTTON_Ok = wxID_HIGHEST + 2,
    BUTTON_NewSH = wxID_HIGHEST + 3,
    BUTTON_Open = wxID_HIGHEST + 4,
    CHOICE_ProdType = wxID_HIGHEST + 5,
    BUTTON_CliIdOK = wxID_HIGHEST + 6,
    BUTTON_ProdAddOK = wxID_HIGHEST + 7,
    BUTTON_ProdRemOK = wxID_HIGHEST + 8
};
