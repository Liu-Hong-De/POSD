// For compilers that supports precompilation , includes "wx/wx.h"

#include "wx/wx.h"
#include "text_frame.h"

TextFrame::TextFrame(const wxChar *title, int xpos, int ypos, int width, int height)
: wxFrame((wxFrame *) NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
{
	m_pTextCtrl = new wxTextCtrl(this, -1, _T("Type some text..."),
		wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

	CreateStatusBar(3);
	SetStatusText(_T("Ready"), 0);
	SetStatusText(_T("To"), 1);
	SetStatusText(_T("Go..."), 2);

	m_pMenuBar = new wxMenuBar();
	// File menu
	m_pFileMenu = new wxMenu();
	m_pFileMenu->Append(wxID_OPEN, _T("&Open"), _T("Opens an existing file"));
	m_pFileMenu->Append(wxID_SAVE, _T("&Save"), _T("Save the content"));
	m_pFileMenu->AppendSeparator();
	m_pFileMenu->Append(wxID_EXIT, _T("&Quit"), _T("Quit the application"));
	m_pMenuBar->Append(m_pFileMenu, _T("&File"));

	// About menu
	m_pHelpMenu = new wxMenu();
	// m_pHelpMenu->Append(wxID_ABOUT, _T("&About"), _T("Shows information about the application"));
	m_pHelpMenu->Append(MENU_About, _T("&About"), _T("Shows information about the application"));
	m_pMenuBar->Append(m_pHelpMenu, _T("&Info"));

	SetMenuBar(m_pMenuBar);

	// m_Hello = new wxButton(this, BUTTON_Hello, _T("Hello"), wxDefaultPosition, wxDefaultSize, 0);
	Layout();
  Centre();
}

// If you're doing an application by inheriting from wxApp
// be sure to change wxFrame to wxApp (or whatever component
// you've inherited your class from).
BEGIN_EVENT_TABLE(TextFrame, wxFrame)
	EVT_MENU(wxID_OPEN, TextFrame::OnMenuFileOpen)
	EVT_MENU(wxID_SAVE, TextFrame::OnMenuFileSave)
	EVT_MENU(wxID_EXIT, TextFrame::OnMenuFileQuit)
	EVT_MENU(MENU_About, TextFrame::OnMenuHelpAbout)
	EVT_BUTTON(BUTTON_Hello, TextFrame::OnHello)
END_EVENT_TABLE()

void TextFrame::OnMenuFileOpen(wxCommandEvent &event)
{
	wxFileDialog *OpenDialog= new wxFileDialog(this, _T("Choose a file"), _(""), _(""), _("*.*"), wxFD_OPEN);
	if ( OpenDialog->ShowModal() == wxID_OK )
	{
		m_pTextCtrl->LoadFile(OpenDialog->GetPath()) ?
			SetStatusText(_T("Loaded")) :
			SetStatusText(_T("Load Failed")) ;
	}
	OpenDialog->Close(); // Or OpenDialog->Destroy() ?
}

void TextFrame::OnMenuFileSave(wxCommandEvent &event)
{
	wxFileDialog *SaveDialog= new wxFileDialog(this, _T("Choose a file"), _(""), _(""), _("*.*"), wxFD_SAVE);
	if ( SaveDialog->ShowModal() == wxID_OK )
	{
		m_pTextCtrl->SaveFile(SaveDialog->GetPath()) ?
			SetStatusText(_T("Saved")) :
			SetStatusText(_T("Save Failed"));
	}
	SaveDialog->Close();
}

void TextFrame::OnMenuFileQuit(wxCommandEvent &event)
{
	Close(false);
}

void TextFrame::OnMenuHelpAbout(wxCommandEvent &event)
{
	wxLogMessage(wxT("The Simple Text Editor"));
}

void TextFrame::OnHello(wxCommandEvent & event) {
	SetStatusText(_T("Hello"), 0);
  SetStatusText(_T("To"), 1);
  SetStatusText(_T("You!!!"), 2);
}
