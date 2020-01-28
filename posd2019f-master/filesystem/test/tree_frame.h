#ifndef TREE_FRAME_H
#define TREE_FRAME_H

#include <wx/treectrl.h>

#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

class TreeFrame : public wxFrame
{
public:
  TreeFrame(const wxChar *title, int xpos, int ypos, int width, int height):wxFrame((wxFrame *) NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
  {
    _tree = new wxTreeCtrl(this, wxID_ANY, wxPoint(0,0), wxSize(100,200), wxTR_DEFAULT_STYLE | wxTR_SINGLE);

    Node * folder_1 = new Folder("./test/test_folder/hw");
    Node * a_out = new File("./test/test_folder/hw/a.out");
    Node * test_data = new Folder("./test/test_folder");
    Node * hello_cpp = new File("./test/test_folder/hw/hw1.cpp");

    folder_1->addChild(a_out);
    test_data->addChild(folder_1);
    folder_1->addChild(hello_cpp);

    wxTreeItemId rootId = _tree->AddRoot(test_data->name().c_str());
    growTree(rootId, test_data);

    _tree->ExpandAllChildren(rootId);
  }

  wxTreeCtrl *_tree;

private:
  void growTree(wxTreeItemId rootId, Node * rootNode)
  {
    Node::Iterator * it = rootNode->createIterator();
    for (it->first(); !it->isDone(); it->next()) {
      wxTreeItemId nodeId = _tree->AppendItem(rootId, it->currentItem()->name().c_str());
      growTree(nodeId, it->currentItem());
    }
  }
};

#endif
