#include "funcs.h"
#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Здесь проcто интерфейс
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IMPLEMENT_APP(MyApp);

enum {
  ID_pref = 2,
  ID_alert = 3,
  ID_info = 4,
  ID_start = 5,
  ID_confirm = 6,
  ID_clear = 7,
  ID_reg = 8,
  ID_login = 9,
  ID_file = 10
};

bool MyApp::OnInit() {
  Simple *simple = new Simple("Chost of Vitebsk");
  simple->Show(true);
  return true;
}

Simple::Simple(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)) {
  tc = new wxTextCtrl(this, -1, wxT(""), wxPoint(0, 0), wxSize(250, 30));
  tc1 = new wxTextCtrl(this, -1, wxT(""), wxPoint(0, 0), wxSize(250, 30));
  button = new wxButton(this, ID_reg, wxT("Register"));
  Connect(ID_reg, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(Simple::Click1));
  button->SetFocus();
  button1 = new wxButton(this, ID_login, wxT("Log in"));
  Connect(ID_login, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(Simple::Click1));
  button1->SetFocus();
  text1 = new wxStaticText(this, wxID_ANY, "Enter Username: ", wxPoint(10, 10),
                           wxDefaultSize, wxALIGN_CENTRE);
  text2 = new wxStaticText(this, wxID_ANY, "Enter Password: ", wxPoint(10, 10),
                           wxDefaultSize, wxALIGN_CENTRE);
  topsizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(topsizer);
  topsizer->Add(text1, 0, wxEXPAND | wxALL, 15);
  topsizer->Add(tc, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 70);
  topsizer->Add(text2, 0, wxEXPAND | wxALL, 15);
  topsizer->Add(tc1, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 70);
  wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
  button_sizer->Add(button, 0, wxALL, 20);
  button_sizer->Add(button1, 0, wxALL, 20);
  topsizer->Add(button_sizer, 0, wxALIGN_CENTER);
  topsizer->SetSizeHints(this);
  wxMenu *file = new wxMenu;
  wxMenu *file2 = new wxMenu;
  wxMenu *file3 = new wxMenu;
  menubar = new wxMenuBar;
  file->Append(ID_pref, wxT("&Preferences\tCtrl-P"));
  file2->Append(ID_info, wxT("&About\tCtrl-A"));
  file3->Append(wxID_EXIT, wxT("&Quit"));
  file->AppendSeparator();
  menubar->Append(file, wxT("&Settings"));
  menubar->Append(file2, wxT("&Help"));
  menubar->Append(file3, wxT("Quit"));
  Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
          wxCommandEventHandler(Simple::ShowMessage));
  Connect(ID_pref, wxEVT_COMMAND_MENU_SELECTED,
          wxCommandEventHandler(Simple::OnOpen));
  Connect(ID_info, wxEVT_COMMAND_MENU_SELECTED,
          wxCommandEventHandler(Simple::ShowInfo));
  SetMenuBar(menubar);
  Centre();
}

void Simple::Chat(wxString str) {
  delete text1;
  delete text2;
  delete tc;
  delete tc1;
  delete button;
  delete button1;
  wxStaticText *text1 = new wxStaticText(this, wxID_ANY, str, wxPoint(10, 10),
                                         wxSize(100, 20), wxALIGN_CENTRE);
  MainEditBox =
      new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1), wxSize(600, 30),
                     wxTE_RICH, wxDefaultValidator, "");
  MsgHistory =
      new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1), wxSize(600, 250),
                     wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, "");
  MsgHistory->SetEditable(false);
  wxButton *button1 = new wxButton(this, ID_confirm, wxT("Send"));
  Connect(ID_confirm, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(Simple::Confirm));
  button1->SetFocus();
  wxButton *button3 = new wxButton(this, ID_file, wxT("Attach File"));
  Connect(ID_file, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(Simple::OnOpen));
  button3->SetFocus();
  wxButton *button2 = new wxButton(this, ID_clear, wxT("Clear"));
  Connect(ID_clear, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(Simple::Clear));
  button1->SetFocus();
  wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
  wxMenu *file4 = new wxMenu;
  file4->Append(wxID_EXIT, wxT("Manage Chats\tAlt-C"));
  menubar->Append(file4, wxT("Chats"));
  SetSizer(topsizer);

  topsizer->Add(text1, 0, wxEXPAND | wxALL, 10);
  topsizer->Add(MsgHistory, 1, wxEXPAND | wxALL, 15);
  topsizer->Add(MainEditBox, 0, wxEXPAND | wxLEFT | wxRIGHT, 15);
  wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
  button_sizer->Add(button1, 0, wxALL, 20);
  button_sizer->Add(button3, 0, wxALL, 20);
  button_sizer->Add(button2, 0, wxALL, 20);
  topsizer->Add(button_sizer, 0, wxALIGN_CENTER);
  topsizer->SetSizeHints(this);
}

void Simple::Click1(wxCommandEvent &event) {
  unsigned hash = 0;
  string str = tc1->GetValue().ToStdString();
  for (int i = 0; i < str.size(); i++) {
    hash += (int)str[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  cout << "Username: " << tc->GetValue() << endl;
  cout << "Password(encrypted): " << hash << endl;
  Chat(wxT("Здесь будет айпи сервера"));
}

void Simple::ShowMessage(wxCommandEvent &event) {
  int dialog_return_value = wxNO;
  wxMessageDialog *dial =
      new wxMessageDialog(NULL, wxT("Are you sure to quit?"), wxT(""),
                          wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
  dialog_return_value = dial->ShowModal();
  if (dialog_return_value == wxID_YES) {
    Close(true);
  }
}

void Simple::ShowInfo(wxCommandEvent &event) {
  wxMessageDialog *var =
      new wxMessageDialog(NULL, wxT("Made by Ghost of Vitebsk and Max Qwerty"),
                          wxT(""), wxOK | wxICON_NONE);
  var->ShowModal();
}

void Simple::OnOpen(wxCommandEvent &event) {
  wxFileDialog *openFileDialog = new wxFileDialog(this);
  if (openFileDialog->ShowModal() == wxID_OK) {
    wxString fileName = openFileDialog->GetPath();
    MsgHistory->AppendText(wxT("[YOU]: ") + fileName + wxT("\n"));
  }
}

void Simple::Confirm(wxCommandEvent &event) {
  wxDateTime now = wxDateTime::Now();
  wxString date1 = now.Format();
  wxString s = MainEditBox->GetValue();
  MsgHistory->AppendText(wxT("[") + date1 + wxT("] YOU: ") + s + wxT("\n"));
  MainEditBox->Clear();
}

void Simple::Clear(wxCommandEvent &event) { MsgHistory->Clear(); }
