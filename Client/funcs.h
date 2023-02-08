#ifndef FUNCS_H
#define FUNCS_H

#include <wx/wx.h>

class MyApp: public wxApp{
public:
    virtual bool OnInit();
};

class Simple: public wxFrame{
public:
    Simple(const wxString& title);
    void ShowMessage(wxCommandEvent& event);
    void ShowInfo(wxCommandEvent& event);
    void Confirm(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void Click1(wxCommandEvent& event);
    void Click2(wxCommandEvent& event);
    void Clear(wxCommandEvent& event);
    void Select();
    void Chat();
    wxTextCtrl *MainEditBox;
    wxGridSizer* gridSizer;
    wxBoxSizer *topsizer;
    wxStaticText *text1;
    wxStaticText *text2;
    wxStaticText *text3;
    wxStaticText *text4;
    wxMenuBar *menubar;  
    wxButton* button; 
    wxButton* button1; 
    wxTextCtrl *tc;
    wxTextCtrl *tc1;
    wxMenu *file;
}; 

#endif







