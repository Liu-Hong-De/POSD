#include "find_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node.h"
#include "iterator.h"

#include <vector>
#include <string>
using namespace std;

FindVisitor::FindVisitor(string name): _name(name)  // Name is the target we want to find.
{

}

void FindVisitor::visitFolder(Folder * folder) {
  Iterator *it = folder->createIterator();

  if(currentNode == nullptr) {  // 判斷目前節點的上一節點
    allnodepath.clear();
    allnode.clear();
    flag = 0;
    nowNode = nullptr;
  }

  if(flag == 0) { // 判斷是否為起始節點
    nowNode = folder;
    flag = 1;
  }

  allnode.push_back(folder);
  allnodepath.push_back(folder->getPath());
  for (it->first(); !it->isDone(); it->next()) {
    currentNode = folder;
    it->currentItem()->accept(this);
  }
  currentNode = nullptr;
}

void FindVisitor::visitFile(File * file) {
  if(currentNode == nullptr) {
    allnodepath.clear();
    allnode.clear();
    flag = 0;
    nowNode = nullptr;
  }
  if(flag == 0) {
    nowNode = file;
    flag = 1;
  }
  allnode.push_back(file);
  allnodepath.push_back(file->getPath());
  currentNode = nullptr;
}

void FindVisitor::visitLink(Link * link){
  if(currentNode == nullptr) {
    allnodepath.clear();
    allnode.clear();
    flag = 0;
    nowNode = nullptr;
  }
  if(flag == 0) {
    nowNode = link;
    flag = 1;
  }
  allnode.push_back(link);
  allnodepath.push_back(link->getPath());
  currentNode = nullptr;
} // You only need to check the link itself,and you don't have to check the node that the link point to!

string FindVisitor::findResult() {
  string ans = "";
  int num = 0;

  for(int i = 1; i < allnodepath.size(); i++) { // 處理每一節點之path
    allnodepath[i] = "." + allnodepath[i].substr(nowNode->getPath().length(), allnodepath[i].length()-1);
  }

  for(int i = 1; i < allnode.size(); i++) { // 計算答案個數
    if(_name == allnode[i]->name()) {
      num++;
    }
  }

  if(num == 0) {
    if(nowNode->fileOrNot() == "file" && allnode[0]->name() == _name) {  // file itself
      ans += nowNode->name();
    }
    else if(nowNode->fileOrNot() == "folder" && allnode[0]->name() == _name) {  // folder itself
      ans += "";
    }
    else if(nowNode->fileOrNot() == "link" && allnode[0]->name() == _name) {  // link itself
      ans += nowNode->name();
    }
  }
  else if(num == 1) {
    for(int i = 1; i < allnode.size(); i++) {
      if(_name == allnode[i]->name()) {
          ans += allnodepath[i];
      }
    }
  }
  else if(num >= 2) {
    for(int i = 1; i < allnode.size(); i++) {   // find same name file
      if(_name == allnode[i]->name()) {
        ans += allnodepath[i];
        ans += "\n";
      }
    }
    ans = ans.substr(0, ans.length()-1);
  }

  allnodepath.clear();    // clear to reuse
  allnode.clear();
  flag = 0;
  nowNode = nullptr;
  return ans;
}
