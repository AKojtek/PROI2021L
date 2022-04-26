#include "MainFrame.h"
#include "ExtraFrame.h"

MainFrame::MainFrame(Storehouse* m_sh)
    : wxFrame(NULL, wxID_ANY, (*m_sh).getName(), wxDefaultPosition, wxSize(800, 575))
{
    sh = m_sh;
    drawing_width = std::min(250, sh->getSize().first * 250 / sh->getSize().second);
    drawing_length = std::min(250, sh->getSize().second * 250 / sh->getSize().first);

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Save, "&Save...\tCtrl-S",
        "Save current storehouse state to file");
    menuFile->Append(ID_Open, "&Open...\tCtrl-O",
        "Open saved storehouse state from file");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuNew = new wxMenu;
    menuNew->Append(ID_NewClient, "Client",
        "Add a new client");
    menuNew->Append(ID_NewProduct, "Product",
        "Add a new product");

    wxMenu* menuRemove = new wxMenu;
    menuRemove->Append(ID_RemClient, "Client",
        "Remove a client with given ID");
    menuRemove->Append(ID_RemProduct, "Product",
        "Remove a product with given ID");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuNew, "&Add");
    menuBar->Append(menuRemove, "&Remove");

    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Choose what you want to do");

    wxButton* frame_left_button = new wxButton(this, wxID_ANY, wxEmptyString,
        wxPoint(120, 20), wxSize(5, drawing_width + 10), wxBORDER_NONE);
    frame_left_button->SetBackgroundColour(wxColor("black"));
    frame_left_button->Disable();

    wxButton* frame_top_button = new wxButton(this, wxID_ANY, wxEmptyString,
        wxPoint(120, 20), wxSize(drawing_length + 10, 5), wxBORDER_NONE);
    frame_top_button->SetBackgroundColour(wxColor("black"));
    frame_top_button->Disable();

    wxButton* frame_right_button = new wxButton(this, wxID_ANY, wxEmptyString,
        wxPoint(drawing_length + 125, 20), wxSize(5, drawing_width + 10), wxBORDER_NONE);
    frame_right_button->SetBackgroundColour(wxColor("black"));
    frame_right_button->Disable();

    wxButton* frame_bottom_button = new wxButton(this, wxID_ANY, wxEmptyString,
        wxPoint(120, drawing_width + 25), wxSize(drawing_length + 10, 5), wxBORDER_NONE);
    frame_bottom_button->SetBackgroundColour(wxColor("black"));
    frame_bottom_button->Disable();

    UpdateDrawing();

    wxButton* rearrange_button = new wxButton(this, BUTTON_Rearrange, _T("Rearrange"),
        wxPoint(500, 70), wxSize(100, 50), 0);
    wxButton* get_receipt_button = new wxButton(this, BUTTON_GetReceipt, _T("Get Receipt"),
        wxPoint(605, 70), wxSize(100, 50), 0);
    wxButton* new_cli_button = new wxButton(this, BUTTON_NewCli, _T("Add Client"),
        wxPoint(500, 125), wxSize(100, 50), 0);
    wxButton* rem_cli_button = new wxButton(this, BUTTON_RemCli, _T("Remove Client"),
        wxPoint(605, 125), wxSize(100, 50), 0);
    wxButton* new_prod_button = new wxButton(this, BUTTON_NewProd, _T("Add Product"),
        wxPoint(500, 180), wxSize(100, 50), 0);
    wxButton* rem_prod_button = new wxButton(this, BUTTON_RemProd, _T("Remove Product"),
        wxPoint(605, 180), wxSize(100, 50), 0);

    std::ostringstream oss;
    oss << *sh;

    sh_details_txt = new wxTextCtrl(this, -1, oss.str(),
        wxPoint(0, 300), wxSize(800, 200), wxTE_READONLY | wxTE_MULTILINE | wxHSCROLL);

    Bind(wxEVT_MENU, &MainFrame::OnSave, this, ID_Save);
    Bind(wxEVT_MENU, &MainFrame::OnOpen, this, ID_Open);
    Bind(wxEVT_MENU, &MainFrame::OnQuit, this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnExit, this);

    Bind(wxEVT_BUTTON, &MainFrame::OnRearrange, this, BUTTON_Rearrange);
    Bind(wxEVT_BUTTON, &MainFrame::OnGetReceipt, this, BUTTON_GetReceipt);
    Bind(wxEVT_BUTTON, &MainFrame::OnNewClient, this, BUTTON_NewCli);
    Bind(wxEVT_BUTTON, &MainFrame::OnRemClient, this, BUTTON_RemCli);
    Bind(wxEVT_BUTTON, &MainFrame::OnNewProduct, this, BUTTON_NewProd);
    Bind(wxEVT_BUTTON, &MainFrame::OnRemProduct, this, BUTTON_RemProd);

    Bind(wxEVT_MENU, &MainFrame::OnNewClient, this, ID_NewClient);
    Bind(wxEVT_MENU, &MainFrame::OnNewProduct, this, ID_NewProduct);
    Bind(wxEVT_MENU, &MainFrame::OnRemClient, this, ID_RemClient);
    Bind(wxEVT_MENU, &MainFrame::OnRemProduct, this, ID_RemProduct);
}

void MainFrame::Update()
{
    std::ostringstream oss;
    oss << *sh;
    sh_details_txt->Clear();
    *sh_details_txt << oss.str();
}

void MainFrame::UpdateDrawing()
{
    for (auto prod_button : product_buttons)
        delete prod_button;
    product_buttons.clear();

    for (auto prod : sh->getProducts().products)
    {
        wxButton* product_button = new wxButton(this, wxID_ANY,
            std::to_string(prod->product->getID()),
            wxPoint(prod->leftY * drawing_width / sh->getSize().first + 125,
                prod->leftX * drawing_length / sh->getSize().second + 25),
            wxSize((prod->rightY - prod->leftY) * drawing_width / sh->getSize().first,
                (prod->rightX - prod->leftX) * drawing_length / sh->getSize().second),
            wxBORDER_NONE);
        if (prod->productType == "Exclusive")
            product_button->SetBackgroundColour(wxColor("pink"));
        else
            product_button->SetBackgroundColour(wxColor("cyan"));

        product_buttons.push_back(product_button);
    }
}

void MainFrame::OnSave(wxCommandEvent& event)
{
    sh_details_txt->Clear();
    *sh_details_txt << prepareForFile(*sh);
    
    wxString file_path = wxSaveFileSelector("Storehouse State", "tsv", sh->getName() + ".tsv");
    if (file_path == wxEmptyString)
        return;

    sh_details_txt->SaveFile(file_path);

    std::ostringstream oss;
    oss << *sh;
    sh_details_txt->Clear();
    *sh_details_txt << oss.str();
}

void MainFrame::OnOpen(wxCommandEvent& event)
{
    wxString file_path = wxLoadFileSelector("Storehouse State", "tsv", "storehouse.tsv");
    if (file_path == wxEmptyString)
        return;

    sh_details_txt->LoadFile(file_path);

    std::string loaded_in = std::string(sh_details_txt->GetValue());
    std::istringstream iss(loaded_in);
    *sh = Storehouse();
    sh->setStorehouse(iss);

    std::ostringstream oss;
    oss << *sh;
    sh_details_txt->Clear();
    *sh_details_txt << oss.str();
}

void MainFrame::OnQuit(wxCommandEvent& event)
{
    Close(true);
}

void MainFrame::OnExit(wxCloseEvent& event)
{
    sh_details_txt->Clear();
    *sh_details_txt << prepareForFile(*sh);
    sh_details_txt->SaveFile("storehouse.tsv");

    for (auto prod_button : product_buttons)
        delete prod_button;
    product_buttons.clear();

    delete sh;
    Destroy();
}

void MainFrame::OnRearrange(wxCommandEvent& event)
{
    sh->rearrange();
    Update();
    UpdateDrawing();
}

void MainFrame::OnGetReceipt(wxCommandEvent& event)
{
    GetReceiptFrame* get_receipt_frame = new GetReceiptFrame(this);
    get_receipt_frame->Show(true);
}

void MainFrame::OnNewClient(wxCommandEvent& event)
{
    NewClientFrame* new_client_frame = new NewClientFrame(this);
    new_client_frame->Show(true);
}

void MainFrame::OnNewProduct(wxCommandEvent& event)
{
    NewProductFrame* new_product_frame = new NewProductFrame(this);
    new_product_frame->Show(true);
}

void MainFrame::OnRemClient(wxCommandEvent& event)
{
    int rem_cli_id = wxGetNumberFromUser(
        "Remove client with given ID\nIn case of absence of given ID,\nnothing will be done",
        "ID", "Remove Client", 0, 0, 99999999);
    if (rem_cli_id == -1)
        return;

    if (!(sh->removeClient(rem_cli_id)))
    {
        wxLogMessage("No client with given ID.\nNothing was done.");
        return;
    }
    Update();
    UpdateDrawing();
}

void MainFrame::OnRemProduct(wxCommandEvent& event)
{
    int rem_prod_id = wxGetNumberFromUser(
        "Remove product with given ID\nIn case of absence of given ID,\nnothing will be done",
        "ID", "Remove Product", 0, 0, 99999999);
    if (rem_prod_id == -1)
        return;

    if (sh->isExclusive(rem_prod_id))
    {
        int attempts = 0;
        while (!sh->verifyOwnership(rem_prod_id,
            std::string(wxGetPasswordFromUser(
                "Enter password to remove Exclusive product",
                "Enter Password"))))
        {
            attempts++;
            if (attempts >= 3)
            {
                wxLogMessage("Wrong password entered 3 times. Product will not be removed.\nTry again later.");
                return;
            }
        }
    }

    if (!(sh->removeProduct(rem_prod_id)))
    {
        wxLogMessage("No product with given ID.\nNothing was done.");
        return;
    }
    Update();

    for (int i = 0; i < product_buttons.size(); i++)
    {
        if (std::string(product_buttons[i]->GetLabel()) == std::to_string(rem_prod_id))
        {
            delete product_buttons[i];
            product_buttons.erase(product_buttons.begin() + i);
            break;
        }
    }
}
