#include "ExtraFrame.h"

ExtraFrame::ExtraFrame(std::string name, MainFrame* m_parent)
    : wxFrame(m_parent, wxID_ANY, name)
{
    parent = m_parent;
    
    cancel_button = new wxButton(this, BUTTON_Cancel, _T("Cancel"),
        wxPoint(250, 325), wxSize(100, 50), 0);
    ok_button = new wxButton(this, BUTTON_Ok, _T("OK"),
        wxPoint(50, 325), wxSize(100, 50), 0);
    Bind(wxEVT_BUTTON, &ExtraFrame::OnExit, this, BUTTON_Cancel);
}

void ExtraFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}


EntryFrame::EntryFrame()
    : ExtraFrame("Storehouse Simulator")
{
    wxStaticText* title_text = new wxStaticText(this, -1,
        wxT("Welcome to Storehouse Simulator!"),
        wxPoint(50, 25), wxSize(300, 50), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    title_text->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxStaticText* new_sh_text = new wxStaticText(this, -1,
        wxT("Begin with a new storehouse..."),
        wxPoint(50, 100), wxSize(300, 25), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    new_sh_text->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxButton* new_sh_button = new wxButton(this, BUTTON_NewSH, _T("New"),
        wxPoint(160, 130), wxSize(80, 40), 0);

    wxStaticText* open_text = new wxStaticText(this, -1,
        wxT("... or open from file..."),
        wxPoint(50, 185), wxSize(300, 25), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    open_text->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxButton* open_button = new wxButton(this, BUTTON_Open, _T("Open"),
        wxPoint(160, 215), wxSize(80, 40), 0);

    wxStaticText* cont_text = new wxStaticText(this, -1,
        wxT("... or continue where you last left"),
        wxPoint(50, 275), wxSize(300, 25), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    cont_text->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    ok_button->SetLabelText("Continue");

    Bind(wxEVT_BUTTON, &EntryFrame::OnOpen, this, BUTTON_Open);
    Bind(wxEVT_BUTTON, &EntryFrame::OnNewSH, this, BUTTON_NewSH);
    Bind(wxEVT_BUTTON, &EntryFrame::OnOK, this, BUTTON_Ok);
}

void EntryFrame::OnNewSH(wxCommandEvent& event)
{
    NewStorehouseFrame* new_sh_frame = new NewStorehouseFrame;
    new_sh_frame->Show(true);
    Close(true);
}

void EntryFrame::OnOpen(wxCommandEvent& event)
{
    std::string file_path = std::string(wxLoadFileSelector("Storehouse", "tsv", "storehouse.tsv"));
    if (file_path == wxEmptyString)
        return;

    Storehouse* sh = new Storehouse;
    std::ifstream is(file_path);
    sh->setStorehouse(is);
    is.close();

    MainFrame* frame = new MainFrame(sh);
    frame->Show(true);

    Close(true);
}

void EntryFrame::OnOK(wxCommandEvent& event)
{
    Storehouse* sh = new Storehouse;
    std::ifstream is("storehouse.tsv");
    sh->setStorehouse(is);
    is.close();

    MainFrame* frame = new MainFrame(sh);
    frame->Show(true);

    Close(true);
}


NewStorehouseFrame::NewStorehouseFrame()
    : ExtraFrame("New Storehouse")
{
    CreateStatusBar();
    SetStatusText("Fill in information about the new storehouse");

    wxStaticText* title_text = new wxStaticText(this, -1,
        wxT("Add new storehouse"),
        wxPoint(50, 25), wxSize(300, 50), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    title_text->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxStaticText* direc_text = new wxStaticText(this, -1,
        wxT("Please enter storehouse details"),
        wxPoint(50, 70), wxSize(300, 25), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    direc_text->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    sh_name_edit = new wxTextCtrl(this, -1, wxT("Storehouse Name"),
        wxPoint(50, 100), wxSize(300, 20), 0);

    wxStaticText* width_text = new wxStaticText(this, -1,
        wxT("Storehouse width:"),
        wxPoint(50, 125), wxSize(100, 20), wxST_NO_AUTORESIZE);

    sh_width_edit = new wxSpinCtrl(this, wxID_ANY, "",
        wxPoint(200, 125), wxSize(150, 20), wxSP_ARROW_KEYS, 1, 200, 10);

    wxStaticText* length_text = new wxStaticText(this, -1,
        wxT("Storehouse length:"),
        wxPoint(50, 150), wxSize(100, 20), wxST_NO_AUTORESIZE);

    sh_length_edit = new wxSpinCtrl(this, wxID_ANY, "",
        wxPoint(200, 150), wxSize(150, 20), wxSP_ARROW_KEYS, 1, 200, 10);

    wxStaticText* shortterm_time_text = new wxStaticText(this, -1,
        wxT("ShortTerm limit (days):"),
        wxPoint(50, 175), wxSize(125, 20), wxST_NO_AUTORESIZE);

    shortterm_time_edit = new wxSpinCtrl(this, wxID_ANY, "",
        wxPoint(200, 175), wxSize(150, 20), wxSP_ARROW_KEYS, 0, 9999999);

    wxStaticText* penalty_mult_text = new wxStaticText(this, -1,
        wxT("Penalty multiplier:"),
        wxPoint(50, 200), wxSize(125, 20), wxST_NO_AUTORESIZE);

    penalty_mult_edit = new wxSpinCtrl(this, wxID_ANY, "",
        wxPoint(200, 200), wxSize(150, 20), wxSP_ARROW_KEYS, 1, 9999999, 1);

    wxStaticText* longterm_cost_text = new wxStaticText(this, -1,
        wxT("LongTerm cost:"),
        wxPoint(50, 225), wxSize(125, 20), wxST_NO_AUTORESIZE);

    longterm_cost_edit = new wxSpinCtrl(this, wxID_ANY, "",
        wxPoint(200, 225), wxSize(150, 20), wxSP_ARROW_KEYS, 0, 9999999);

    wxStaticText* shortterm_cost_text = new wxStaticText(this, -1,
        wxT("ShortTerm cost:"),
        wxPoint(50, 250), wxSize(125, 20), wxST_NO_AUTORESIZE);

    shortterm_cost_edit = new wxSpinCtrl(this, wxID_ANY, "",
        wxPoint(200, 250), wxSize(150, 20), wxSP_ARROW_KEYS, 0, 9999999);

    wxStaticText* exclusive_cost_text = new wxStaticText(this, -1,
        wxT("Exclusive cost:"),
        wxPoint(50, 275), wxSize(125, 20), wxST_NO_AUTORESIZE);

    exclusive_cost_edit = new wxSpinCtrl(this, wxID_ANY, "",
        wxPoint(200, 275), wxSize(150, 20), wxSP_ARROW_KEYS, 0, 9999999);

    wxStaticText* wholesale_cost_text = new wxStaticText(this, -1,
        wxT("Wholesale cost:"),
        wxPoint(50, 300), wxSize(125, 20), wxST_NO_AUTORESIZE);

    wholesale_cost_edit = new wxSpinCtrl(this, wxID_ANY, "",
        wxPoint(200, 300), wxSize(150, 20), wxSP_ARROW_KEYS, 0, 9999999);

    Bind(wxEVT_BUTTON, &NewStorehouseFrame::OnOK, this, BUTTON_Ok);
    Bind(wxEVT_BUTTON, &NewStorehouseFrame::OnCancel, this, BUTTON_Cancel);
}

void NewStorehouseFrame::OnOK(wxCommandEvent& event)
{
    std::string sh_name = std::string(sh_name_edit->GetValue());
    int sh_width = sh_width_edit->GetValue();
    int sh_length = sh_length_edit->GetValue();
    int shortterm_time = shortterm_time_edit->GetValue();
    int penalty_mult = penalty_mult_edit->GetValue();
    int lt_cost = longterm_cost_edit->GetValue();
    int st_cost = shortterm_cost_edit->GetValue();
    int ex_cost = exclusive_cost_edit->GetValue();
    int ws_cost = wholesale_cost_edit->GetValue();

    Storehouse* sh = new Storehouse(sh_name, std::make_pair(sh_width, sh_length));
    sh->setReceiptValues(shortterm_time, penalty_mult, lt_cost, st_cost, ex_cost, ws_cost);

    MainFrame* frame = new MainFrame(sh);
    frame->Show(true);

    Close(true);

    Close(true);
}

void NewStorehouseFrame::OnCancel(wxCommandEvent& event)
{
    Close(true);
    EntryFrame* entry_frame = new EntryFrame();
    entry_frame->Show(true);
}


NewClientFrame::NewClientFrame(MainFrame* m_parent)
    : ExtraFrame("Add Client", m_parent)
{
    CreateStatusBar();
    SetStatusText("Fill in the new client's data");

    wxStaticText* title_text = new wxStaticText(this, -1,
        wxT("Add new client"),
        wxPoint(50, 50), wxSize(300, 50), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    title_text->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxStaticText* direc_text = new wxStaticText(this, -1,
        wxT("Please enter client details"),
        wxPoint(50, 110), wxSize(300, 25), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    direc_text->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    std::string id_str = "ID: " + std::to_string(parent->sh->getProducts().findSmallestMissingCli());
    wxStaticText* id_text = new wxStaticText(this, -1, id_str,
        wxPoint(50, 140), wxSize(300, 20), wxST_NO_AUTORESIZE);
    id_text->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    cli_name_edit = new wxTextCtrl(this, -1, wxT("Client Name"),
        wxPoint(50, 170), wxSize(300, 20), 0);

    cli_city_edit = new wxTextCtrl(this, -1, wxT("Client Address"),
        wxPoint(50, 195), wxSize(300, 45), wxTE_WORDWRAP | wxTE_MULTILINE);

    cli_phone_edit = new wxTextCtrl(this, -1, wxT("ClientPhone"),
        wxPoint(50, 245), wxSize(300, 20), 0);

    Bind(wxEVT_BUTTON, &NewClientFrame::OnOK, this, BUTTON_Ok);
}

void NewClientFrame::OnOK(wxCommandEvent& event)
{
    int cli_id = parent->sh->getProducts().findSmallestMissingCli();
    std::string cli_name = std::string(cli_name_edit->GetValue());
    std::string cli_city = std::string(cli_city_edit->GetValue());
    std::string cli_phone = std::string(cli_phone_edit->GetValue());

    Client cli = Client(cli_id, cli_name, cli_city, cli_phone);
    parent->sh->addClient(cli);
    parent->Update();

    Close(true);
}


NewProductFrame::NewProductFrame(MainFrame* m_parent)
    : ExtraFrame("Add Product", m_parent)
{
    CreateStatusBar();
    SetStatusText("Fill in information about the new product");

    wxStaticText* title_text = new wxStaticText(this, -1,
        wxT("Add new product"),
        wxPoint(50, 25), wxSize(300, 50), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    title_text->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxStaticText* direc_text = new wxStaticText(this, -1,
        wxT("Please enter product details"),
        wxPoint(50, 75), wxSize(300, 25), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    direc_text->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    prod_owner_id_edit = new wxSpinCtrl(this, wxID_ANY, wxT("Owner ID"),
        wxPoint(50, 100), wxSize(300, 20), wxSP_ARROW_KEYS, 0, 99999999, 0);

    std::string id_str = "Product ID: " + std::to_string(parent->sh->getProducts().findSmallestMissingProd());
    wxStaticText* id_text = new wxStaticText(this, -1, id_str,
        wxPoint(50, 125), wxSize(300, 20), wxST_NO_AUTORESIZE);
    id_text->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    prod_name_edit = new wxTextCtrl(this, -1, wxT("Product Name"),
        wxPoint(50, 150), wxSize(300, 20), 0);

    prod_width_edit = new wxSpinCtrl(this, wxID_ANY, wxT("Product Width"),
        wxPoint(50, 175), wxSize(300, 20), wxSP_ARROW_KEYS, 1, 200, 1);

    prod_height_edit = new wxSpinCtrl(this, wxID_ANY, wxT("Product Height"),
        wxPoint(50, 200), wxSize(300, 20), wxSP_ARROW_KEYS, 1, 200, 1);

    wxString options[] = { "Exclusive", "ShortTerm", "LongTerm", "Wholesale" };
    prod_type_choice = new wxChoice(this, CHOICE_ProdType,
        wxPoint(50, 225), wxSize(300, 25),
        4, options, 0);

    Bind(wxEVT_CHOICE, &NewProductFrame::OnChoice, this, CHOICE_ProdType);
    Bind(wxEVT_BUTTON, &NewProductFrame::OnOK, this, BUTTON_Ok);
}

void NewProductFrame::OnChoice(wxCommandEvent& event)
{
    int selection = prod_type_choice->GetSelection();
    // 0 - Exclusive
    // 1 - ShortTerm
    // 2 - LongTerm
    // 3 - Wholesale

    if (!prod_begin_edit)
    {
        prod_begin_edit = new wxDatePickerCtrl(this, -1, wxDateTime::Now(),
            wxPoint(50, 250), wxSize(300, 20), wxDP_DROPDOWN | wxDP_SHOWCENTURY);
    }

    if (prod_end_edit && selection == 2)
    {
        delete prod_end_edit;
        prod_end_edit = nullptr;
    }
    else if (!prod_end_edit && selection != 2)
    {
        prod_end_edit = new wxDatePickerCtrl(this, -1,
            wxDateTime::Now().Add(
                wxDateSpan(0, 0, 0, std::min(30,  int(parent->sh->getReceipt().getShortTerm() / 86400)))),
            wxPoint(50, 275), wxSize(300, 20), wxDP_DROPDOWN | wxDP_SHOWCENTURY);
    }

    if (selection == 1)
    {
        prod_end_edit->SetRange(wxDateTime::Now(),
            wxDateTime::Now().Add(
                wxDateSpan(0, 0, 0, int(parent->sh->getReceipt().getShortTerm() / 86400))));
    }
    else if (selection != 2)
    {
        prod_end_edit->SetRange(wxDateTime::Now(),
            wxDateTime::Now().Add(wxDateSpan(1000)));
    }

    if (prod_password_edit && selection != 0)
    {
        delete prod_password_edit;
        prod_password_edit = nullptr;
    }
    else if (selection == 0 && !prod_password_edit)
    {
        prod_password_edit = new wxTextCtrl(this, -1, wxT("Password"),
            wxPoint(50, 300), wxSize(300, 20), wxTE_PASSWORD);
    }
}

void NewProductFrame::OnOK(wxCommandEvent& event)
{
    int owner_id = prod_owner_id_edit->GetValue();
    int prod_id = parent->sh->getProducts().findSmallestMissingProd();
    std::string prod_name = std::string(prod_name_edit->GetValue());
    int prod_width = prod_width_edit->GetValue();
    int prod_height = prod_height_edit->GetValue();
    std::string prod_type = std::string(prod_type_choice->GetStringSelection());
    if (prod_type == "")
        return;

    wxDateTime begin_date = prod_begin_edit->GetValue();
    std::string begin_str = std::string(begin_date.Format("%d-%m-%Y"));
    std::time_t begin_time = castStringDate(begin_str);

    std::time_t end_time;
    if (prod_type != "LongTerm")
    {
        wxDateTime end_date = prod_end_edit->GetValue();
        std::string end_str = std::string(end_date.Format("%d-%m-%Y"));
        end_time = castStringDate(end_str);
    }

    if (prod_type == "Exclusive")
    {
        std::string prod_password = std::string(prod_password_edit->GetValue());

        Exclusive* prod = new Exclusive(prod_id, prod_name,
            prod_width, prod_height, begin_time, end_time, prod_password);

        if (!(parent->sh->addProduct(prod, prod_type, owner_id)))
        {
            wxLogMessage("No client with given ID.");
            return;
        }
    }
    else if (prod_type == "ShortTerm")
    {
        ShortTerm* prod = new ShortTerm(prod_id, prod_name,
            prod_width, prod_height, begin_time, end_time);

        if (!(parent->sh->addProduct(prod, prod_type, owner_id)))
        {
            wxLogMessage("No client with given ID.");
            return;
        }
    }
    else if (prod_type == "LongTerm")
    {
        LongTerm* prod = new LongTerm(prod_id, prod_name,
            prod_width, prod_height, begin_time);

        if (!(parent->sh->addProduct(prod, prod_type, owner_id)))
        {
            wxLogMessage("No client with given ID.");
            return;
        }
    }
    else if (prod_type == "Wholesale")
    {
        Wholesale* prod = new Wholesale(prod_id, prod_name,
            prod_width, prod_height, begin_time, end_time);

        if (!(parent->sh->addProduct(prod, prod_type, owner_id)))
        {
            wxLogMessage("No client with given ID.");
            return;
        };
    }
    
    parent->Update();
    addButtonToDrawing(prod_id);

    Close(true);
}

void NewProductFrame::addButtonToDrawing(int id)
{
    ProductInfo* prod = parent->sh->getProducts().getProdInfo(id);

    wxButton* product_button = new wxButton(parent, wxID_ANY,
        std::to_string(prod->product->getID()),
        wxPoint(prod->leftY * parent->drawing_width / parent->sh->getSize().first + 125,
            prod->leftX * parent->drawing_length / parent->sh->getSize().second + 25),
        wxSize((prod->rightY - prod->leftY) * parent->drawing_width / parent->sh->getSize().first,
            (prod->rightX - prod->leftX) * parent->drawing_length / parent->sh->getSize().second),
        wxBORDER_NONE);
    if (prod->productType == "Exclusive")
        product_button->SetBackgroundColour(wxColor("pink"));
    else
        product_button->SetBackgroundColour(wxColor("cyan"));

    parent->product_buttons.push_back(product_button);
}


GetReceiptFrame::GetReceiptFrame(MainFrame* m_parent)
    : ExtraFrame("Get Receipt", m_parent)
{
    cancel_button->SetSize(wxSize(80, 40));
    cancel_button->SetPosition(wxPoint(250, 365));
    ok_button->SetSize(wxSize(80, 40));
    ok_button->SetPosition(wxPoint(50, 365));

    wxStaticText* title_text = new wxStaticText(this, -1,
        wxT("Choose data for receipt"),
        wxPoint(50, 25), wxSize(300, 30), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    title_text->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxStaticText* cli_id_text = new wxStaticText(this, -1,
        wxT("Client ID:"),
        wxPoint(75, 65), wxSize(75, 20), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);

    client_id_edit = new wxSpinCtrl(this, wxID_ANY, "",
        wxPoint(160, 65), wxSize(80, 20), wxSP_ARROW_KEYS, 0, 99999999, 0);

    wxButton* client_id_ok = new wxButton(this, BUTTON_CliIdOK, "OK",
        wxPoint(250, 65), wxSize(50, 20));

    prods_left_txt = new wxTextCtrl(this, -1, "",
        wxPoint(25, 90), wxSize(150, 200), wxTE_READONLY | wxTE_MULTILINE | wxHSCROLL | wxVSCROLL);

    prods_chosen_txt = new wxTextCtrl(this, -1, "",
        wxPoint(200, 90), wxSize(150, 200), wxTE_READONLY | wxTE_MULTILINE | wxHSCROLL | wxVSCROLL);

    wxStaticText* prod_add_text = new wxStaticText(this, -1,
        wxT("ID to add to receipt:"),
        wxPoint(25, 300), wxSize(125, 20), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);

    prod_add_edit = new wxSpinCtrl(this, wxID_ANY, "",
        wxPoint(160, 300), wxSize(80, 20), wxSP_ARROW_KEYS, 0, 99999999, 0);

    wxButton* prod_add_ok = new wxButton(this, BUTTON_ProdAddOK, "OK",
        wxPoint(250, 300), wxSize(50, 20));

    wxStaticText* prod_rem_text = new wxStaticText(this, -1,
        wxT("ID to remove from receipt:"),
        wxPoint(0, 325), wxSize(150, 20), wxALIGN_RIGHT | wxST_NO_AUTORESIZE);

    prod_rem_edit = new wxSpinCtrl(this, wxID_ANY, "",
        wxPoint(160, 325), wxSize(80, 20), wxSP_ARROW_KEYS, 0, 99999999, 0);

    wxButton* prod_rem_ok = new wxButton(this, BUTTON_ProdRemOK, "OK",
        wxPoint(250, 325), wxSize(50, 20));

    Bind(wxEVT_BUTTON, &GetReceiptFrame::OnOK, this, BUTTON_Ok);
    Bind(wxEVT_BUTTON, &GetReceiptFrame::OnCliIdOK, this, BUTTON_CliIdOK);
    Bind(wxEVT_BUTTON, &GetReceiptFrame::OnProdAddOK, this, BUTTON_ProdAddOK);
    Bind(wxEVT_BUTTON, &GetReceiptFrame::OnProdRemOK, this, BUTTON_ProdRemOK);
}

void GetReceiptFrame::OnCliIdOK(wxCommandEvent& event)
{
    prods_left_txt->Clear();
    prods_chosen_txt->Clear();
    
    int client_id = client_id_edit->GetValue();
    parent->sh->changeReceiptClient(client_id);
    *prods_left_txt << parent->sh->NotInReceipt();
}

void GetReceiptFrame::OnProdAddOK(wxCommandEvent& event)
{
    int prod_id = prod_add_edit->GetValue();

    if (parent->sh->shouldVerifyOwnership(prod_id))
    {
        int attempts = 0;
        while (!parent->sh->verifyOwnership(prod_id,
            std::string(wxGetPasswordFromUser(
                "Enter password to add Exclusive product to receipt",
                "Enter Password"))))
        {
            attempts++;
            if (attempts >= 3)
            {
                wxLogMessage("Wrong password entered 3 times. Product will not be added to receipt.\nTry again later.");
                return;
            }
        }
    }
    parent->sh->addReceiptProduct(prod_id);

    prods_left_txt->Clear();
    prods_chosen_txt->Clear();

    *prods_left_txt << parent->sh->NotInReceipt();
    *prods_chosen_txt << parent->sh->InReceipt();
}

void GetReceiptFrame::OnProdRemOK(wxCommandEvent& event)
{
    int prod_id = prod_rem_edit->GetValue();

    parent->sh->removeReceiptProduct(prod_id);

    prods_left_txt->Clear();
    prods_chosen_txt->Clear();

    *prods_left_txt << parent->sh->NotInReceipt();
    *prods_chosen_txt << parent->sh->InReceipt();
}

void GetReceiptFrame::OnOK(wxCommandEvent& event)
{
    if (!parent->sh->isClientSet())
    {
        wxLogMessage("No valid client chosen.");
        return;
    }

    parent->sh->createReceipt();
    wxLogMessage("Receipt created and saved to file.");

    parent->Update();
    parent->UpdateDrawing();

    Close(true);
}
