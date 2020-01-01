#include <wx/wx.h>
#include "tree_test.h"
#include "tree_frame.h"

IMPLEMENT_APP(TreeTestApp)

bool TreeTestApp::OnInit()
{
  // wxFrame *frame = new TreeFrame(wxT("***Tree Test***"), 100,100,300,200);
  wxFrame * frame = new TreeFrame(wxT("***Tree Test***"), 100, 100, 1000, 700);
  frame->Show(true);
  this->SetTopWindow(frame);
  return true;
}
