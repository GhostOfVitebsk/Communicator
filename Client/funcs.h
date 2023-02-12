#ifndef FUNCS_H
#define FUNCS_H

//#include <wx/wx.h>
#include <sys/types.h>
#include <iostream>
#include <sys/socket.h>
#include <string>

using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Здесь функционал
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Client(int port);
void Server(int port);
void Serve(int fd1, int fd2);
void Write(int fd);
void Read(int fd);
void Listen(int sockfd, int backlog);
int Socket(int domain, int type, int protocol);
void Inet_pton(int af, const char *src, void *dst);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Здесь все про GUI
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*class MyApp: public wxApp{
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
    void Chat(wxString str);
    wxTextCtrl *MainEditBox;
    wxTextCtrl *MsgHistory;
    wxTextCtrl *ChatHistory;
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
};*/ 

#endif







