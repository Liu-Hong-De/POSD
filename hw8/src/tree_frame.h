#ifndef TREE_FRAME_H
#define TREE_FRAME_H

#include <wx/treectrl.h>
#include <iostream>
#include <stdio.h>
#include <string>
// #include <stdio.h>
// #include <conio.h>
// #include <curses.h>

#include "filesystem_builder.cpp"
#include "update_path_visitor.cpp"
#include "text_frame.h"

using namespace std;

class TreeFrame : public wxFrame
{
public:
  TreeFrame(const wxChar *title, int xpos, int ypos, int width, int height):wxFrame((wxFrame *) nullptr, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
  {
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    // _tree = new wxTreeCtrl(this, wxID_ANY, wxPoint(0,0), wxSize(150,200), wxTR_DEFAULT_STYLE | wxTR_SINGLE | wxTR_EDIT_LABELS | wxTR_HAS_BUTTONS );
    _tree = new wxTreeCtrl(this, wxID_ANY, wxPoint(0, 0), wxSize(width, height), wxTR_DEFAULT_STYLE | wxTR_SINGLE | wxTR_EDIT_LABELS | wxTR_HAS_BUTTONS );

    // wxTreeItemId rootId = _tree->AddRoot(wxT("Root"));
    // wxTreeItemId folder1Id = _tree->AppendItem(rootId, wxT("Folder1"));
    // wxTreeItemId file1Id = _tree->AppendItem(folder1Id, wxT("File1"));
    // wxTreeItemId file2Id = _tree->AppendItem(rootId, wxT("File2"));

    // _root = new Folder("./test");
    // Node * a_out = new File("./test/file1");
    // Node * test_data = new Folder("./test/test_data");
    // Node * hello_cpp = new File("./test/test_data/file2");

    // folder_1->addChild(a_out);
    // test_data->addChild(folder_1);
    // folder_1->addChild(hello_cpp);

    // wxTreeItemId rootId = _tree->AddRoot(folder_1->name() + ", " + to_string(folder_1->size()));
    // wxTreeItemId folder1Id = _tree->AppendItem(rootId, test_data->name());
    // wxTreeItemId file1Id = _tree->AppendItem(folder1Id, hello_cpp->name());
    // wxTreeItemId file2Id = _tree->AppendItem(rootId, a_out->name());

    string rootName = string(wxGetApp().argv[1].mb_str());
    // cout << par2 << endl;
    FileSystemBuilder * fb = FileSystemBuilder::instance();
    fb->build(rootName);
    _root = fb->getRoot();

    // cout << _root->getPath() << endl;

    wxTreeItemId rootId = _tree->AddRoot(fb->getRoot()->name() + ", " + to_string(fb->getRoot()->size()));
    _root->setWxTreeItemId(rootId);
    growTree(rootId, _root);

    _tree->ExpandAllChildren(rootId);
    _textArea = new wxTextCtrl(_tree, -1, _T("Welcome to POSD_EDITOR"), wxPoint(170,0),  wxSize(700,500), wxTE_MULTILINE);
    // _textArea->SetBackgroundColour("#f1f1f1");
    // _textArea->SetForegroundColour("#aaabad");
    _textArea->Enable(false);

    // panel = new wxPanel(_textArea);

    _saveBtn = new wxButton(this, BUTTON_Hello, _T("Save"), wxPoint(170,510), wxSize(700,100), 0);
    _saveBtn->Enable(false);
  }

  void growTree(wxTreeItemId rootId, Node * rootNode)
  {
    Iterator * it = rootNode->createIterator();
    for (it->first(); !it->isDone(); it->next()) {
      Node * node = it->currentItem();
      wxTreeItemId nodeId = _tree->AppendItem(rootId, it->currentItem()->name() + ", " + to_string(it->currentItem()->size()));
      node->setWxTreeItemId(nodeId);
      // cout << node->name() << endl;
      // cout << it->currentItem()->name() << endl;
      if(it->currentItem()->fileOrNot() == "folder") {
        growTree(nodeId, it->currentItem());
      }
    }
  }

  void DoubleClick(wxTreeEvent& event){
    _tree->EditLabel(event.GetItem());
  }

  void TreeNameEdit(wxTreeEvent& event) {
    wxTreeItemId itemId = event.GetItem();
    Node * node = getNodeById(itemId, _root);
    // cout << node->size() <<endl;

    if(!node){
      // cout<<"NULL!"<<endl;
    }
    else{
      try{
        string newName = event.GetLabel().ToStdString();
        string oldName = _tree->GetItemText(itemId).ToStdString();

        // cout<<"new!! "<<newName<<endl;
        // cout<<"old!! "<<oldName<<endl;
        // cout << node->name().length() << endl;
        // cout << event.GetLabel().ToStdString() << endl;
        // cout << event.GetLabel().ToStdString().substr(0, node->name().length()+2) << endl;

        if(event.GetLabel().ToStdString() == "" || event.GetLabel().ToStdString().substr(0, node->name().length() + 2) == (node->name() + ", ")) {//if noting to change
          _tree->SetItemText(itemId, wxString(oldName));
          event.Veto();
          return;
        }
        // cout<<node->getPath()<<endl;
        int choose = ShowMessageInRename(newName, oldName);

        if(choose == 0) {
          UpdatePathVisitor * upv = new UpdatePathVisitor();
          node->renameNode(newName);
          node->accept(upv);
          // cout<<node->getPath()<<endl;
          _tree->SetItemText(itemId, wxString(newName + ", " + to_string(node->size())));
        }
        else {
          _tree->SetItemText(itemId, wxString(oldName));
        }
      event.Veto();
      } catch(exception e) {
          cout << "exception" << endl;
        }
    // cout<<(a->getChild("file2"))->getPath()<<endl;
    }
  // std::cout << _tree->GetItemText(itemId)<< std::endl;
  }

  Node* getNodeById(wxTreeItemId id, Node* root) {
    if(root->getWxTreeItemId() == id) {
      return root;
    }
    else {
      Iterator * it = root->createIterator();
      for (it->first(); !it->isDone(); it->next()) {
        if(it->currentItem()->getWxTreeItemId() == id) {
          return it->currentItem();
        }
      }

      for(it->first(); !it->isDone(); it->next()) {
        if(it->currentItem()->fileOrNot() == "folder") {
          return getNodeById(id, it->currentItem());
        }
      }
    }
  }

  // 0=>yes  1=>no  2=>cancel  -1=>default
  int ShowMessageInRename(string newName,string oldName) {
    wxMessageDialog *dialog = new wxMessageDialog(NULL,
      wxT("label edited: " + newName + "-- old name was " + oldName), wxT("Confirm"),
      wxYES_NO | wxCANCEL | wxNO_DEFAULT | wxICON_QUESTION);

    switch (dialog->ShowModal()) {
      case wxID_YES:
        // cout << "yes" << endl;
        return 0;
        break;
      case wxID_NO:
        // cout << "no" << endl;
        return 1;
        break;
      case wxID_CANCEL:
        // cout << "cancel" << endl;
        return 2;
        break;
      default:
        // cout << "default" << endl;
        return -1;
    }
  }

  void read_file(wxTreeEvent &event) {
    try{
      wxTreeItemId itemId = event.GetItem();
      _updateItemSize = itemId;

      Node* node = getNodeById(itemId, _root);
      _filePath = node->getPath();

      if(!node) {
        cout << "null" << endl;
      }
      else{
        if(node->fileOrNot() == "file") {
          // WINDOW *w = initscr();
          _textArea = new wxTextCtrl(_tree, -1, _T(""), wxPoint(170,0),  wxSize(700,500), wxTE_MULTILINE);
          _textArea->LoadFile(wxT_2(node->getPath()));
          _saveBtn->Enable(true);
          // if(getch() == '^') {
          //   cout << "wow" << endl;
          // }
        }
        else if(node->fileOrNot() == "folder") {
          _textArea = new wxTextCtrl(_tree, -1, _T(""), wxPoint(170,0),  wxSize(700,500), wxTE_MULTILINE|wxTE_READONLY);
          // _textArea->SetBackgroundColour("#f1f1f1");
          _textArea->Enable(false);
          _saveBtn->Enable(false);
        }
        else {
          _textArea = new wxTextCtrl(_tree, -1, _T("The file is not displayed in the editor because it uses an unsupported text encoding"), wxPoint(170,0),  wxSize(700,500), wxTE_MULTILINE|wxTE_READONLY);
          // _textArea->SetBackgroundColour("#f1f1f1");
          // _textArea->SetForegroundColour("#aaabad");
          _textArea->Enable(false);
          _saveBtn->Enable(false);
        }
      }
    } catch(exception e) {
      cout << e.what() << endl;
    }
  }

  void saveBtn(wxCommandEvent& event) {
    int save_ans = ShowMessage_Save();
    if(save_ans == 0) {
      save();
    }
  }

  void save() {
    _textArea->SaveFile(wxT_2(_filePath));
    Node * node = getNodeById(_updateItemSize, _root);
    updateItemSize(_updateItemSize, node);
  }

  int ShowMessage_Save() {
    wxMessageDialog *dialog= new wxMessageDialog(NULL,
      wxT("You want save?"), wxT("Confirm"),
      wxYES_NO | wxCANCEL | wxNO_DEFAULT | wxICON_QUESTION);
    switch (dialog->ShowModal()) {
      case wxID_YES:
          // cout << "yes" << endl;
          return 0;
          break;
      case wxID_NO:
          // cout << "no" << endl;
          return 1;
          break;
      case wxID_CANCEL:
          // cout << "cancel" << endl;
          return 2;
          break;
      default:
          // cout << "default" << endl;
          return -1;
    }
  }

  void updateItemSize(wxTreeItemId itemId, Node* node) {
    // cout << "update size!:"<< node->getSize() << endl;
    node->updateSize();
    _tree->SetItemText(itemId, wxString(node->name() + ", " + to_string(node->size())));
    _tree->Refresh();
  }

  void saveKey(wxKeyEvent &event) {
    // cout << "key press!!"<< event.GetKeyCode() << endl;
    if(event.GetKeyCode() == 308) {
      getCtrl = true;
    }
    else if(getCtrl == true && event.GetKeyCode() == 83) {
      int save_ans = ShowMessage_Save();
      if(save_ans == 0) {
        save();
      }
      getCtrl = false;
    }
    else {
      getCtrl = false;
      event.Skip();
    }
  }

private:
  DECLARE_EVENT_TABLE()
  // vector <Node*> views;
  // int value;
  Node * _root;
  wxTreeCtrl *_tree;
  wxTextCtrl *_textArea;
  wxButton* _saveBtn;
  string _filePath;
  wxTreeItemId _updateItemSize;
  bool getCtrl = false;
};

BEGIN_EVENT_TABLE(TreeFrame, wxFrame)
  EVT_TREE_END_LABEL_EDIT (wxID_ANY, TreeFrame::TreeNameEdit)
  EVT_TREE_ITEM_ACTIVATED(wxID_ANY,TreeFrame::DoubleClick)
  EVT_TREE_SEL_CHANGED(wxID_ANY,TreeFrame::read_file)
  EVT_CHAR_HOOK(TreeFrame::saveKey)
  EVT_BUTTON(wxID_ANY, TreeFrame::saveBtn)
END_EVENT_TABLE()
#endif
