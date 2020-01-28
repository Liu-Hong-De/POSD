#include <wx/wx.h>
#include "ui_folder_tree.h"
#include "tree_frame.h"

IMPLEMENT_APP(FolderTreeApp)

bool FolderTreeApp::OnInit() wxOVERRIDE
{
  wxFrame *frame = new TreeFrame(wxT("***Tree Test***"), 100,100,300,200);
  frame->Show(true);
  SetTopWindow(frame);
  return true;
}
