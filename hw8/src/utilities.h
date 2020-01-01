// #ifndef UTILITIES_H
// #define UTILITIES_H
//
// #include "node.h"
// #include "folder.h"
// #include "iterator.h"
//
// void infoByteVisitFolder(Folder* folder, int &total);
// void infoByteVisitFile(File* file, int &total);
//
// //pratice here
// int infoByte(Node* node) {
//   int total = 0;
//   Folder * folder = dynamic_cast<Folder *> (node); // down cast
//   if (folder != nullptr) { //it's a folder
//     infoByteVisitFolder(folder, total);
//   }
//   else{ // it's a file
//     File * file = dynamic_cast<File *> (node);
//     if (file != nullptr) {
//       infoByteVisitFile(file, total);
//     }
//   }
//   return total;
// }
//
// // int infoByte(Node *node) {
// //   InfoByteVisitor ibv;
// //   node->accept(ibv);
// //   return ibv.total();
// // }
//
// void infoByteVisitFolder(Folder* folder, int &total) {
//   Iterator * it = folder->createIterator();
//   for(it->first(); !it->isDone(); it->next()){
//     total += it->currentItem()->size();
//   }
// }
//
//
// void infoByteVisitFile(File* file, int &total) {
//   total+= file->size();
// }
//
// #endif
#ifndef UTILITIES_H
#define UTILITIES_H

#include "node.h"
#include "folder.h"
#include "iterator.h"

#include <iostream>

using namespace std;

class Utilities
{
    public:
      // Utilities(std::string path): Node(path) {}
        string listNode(Node* node)
        {
            // You should use iterator pattern to access node in folder!
            // You can use dynamic_cast if you need
            // If node is file that it should throw string "Not a directory"
            // This function is same as Hw4 listNode()
            Folder * folder = dynamic_cast<Folder *> (node); // down cast
            string list;
            vector<string> temp;
            if (folder != nullptr) { //it's a folder
              Iterator * it = folder->createIterator();
              for(it->first(); !it->isDone(); it->next()){
                temp.push_back(it->currentItem()->name());
              }
              sort(temp.begin(), temp.end());
              list = temp[0];
              for(int i = 1; i < temp.size(); i++) {
                list += " ";
                list += temp[i];
              }
              return list;
            }
            else {
              throw(string("Not a directory"));
            }
        }

        // string findNode(Node* node, string name)
        // {
        //     // You should use iterator pattern to access node in folder!
        //     // You can use dynamic_cast if you need
        //     // This function is same as Hw4 findNode()
        //     vector<string> temp;
        //     Folder * folder = dynamic_cast<Folder *> (node);
        //     if(folder != nullptr) {
        //       Iterator * it = folder->createIterator();
        //     }
        //     else {
        //       temp.push_back(name);
        //     }
        // }

  string allNode(Node* node) {  // find which nodes under this folder
    Folder * folder = dynamic_cast<Folder *> (node); // down cast
    string temp;
    if(folder != nullptr) {
      Iterator * it = folder->createIterator();
      for(it->first(); !it->isDone(); it->next()){
        temp += it->currentItem()->name();
        temp += "<>";
        temp += allNode(it->currentItem());
      }
    }

    return temp;
  }

  string allLeaf(Node* node) {  // when find only one folder，find all leaves under this folder
    Folder * folder = dynamic_cast<Folder *> (node); // down cast
    string temp;
    if(folder != nullptr) {
      Iterator * it = folder->createIterator();
        if(!folder->isEmpty()) {
          for(it->first(); !it->isDone(); it->next()) {
            temp += allLeaf(it->currentItem());
          }
        }

      else {
        temp += "";
      }
    }
    else {
      temp += node->name();
      temp += "<>";
    }
    return temp;
  }

  string allNodePath(Node* node, string begin) {  // find all nodes path which are under the folder you want to find
    Folder * folder = dynamic_cast<Folder *> (node); // down cast
    string temp;
    if(folder != nullptr) {
      Iterator * it = folder->createIterator();
      for(it->first(); !it->isDone(); it->next()){
        string child = "";
        temp += begin;
        temp += it->currentItem()->name();
        child += begin;
        child += it->currentItem()->name();
        temp += "<>";

        child += "/";
        temp += allNodePath(it->currentItem(), child);
      }
    }
    return temp;
  }

  vector<string> split(const string& str, const string& delim) {
  	vector<string> res;
  	if("" == str) return res;

  	char * strs = new char[str.length() + 1] ;
  	strcpy(strs, str.c_str());

  	char * d = new char[delim.length() + 1];
  	strcpy(d, delim.c_str());

  	char *p = strtok(strs, d);
  	while(p) {
  		string s = p;
  		res.push_back(s);
  		p = strtok(NULL, d);
  	}

  	return res;
  }

  string findNode(Node* node, string name)
  {
    string temp = allNode(node); // include all node string use <> to seperate
    std::vector<string> allNode = split(temp, "<>"); // because the file or folder name can not have <>

    string temp_path = allNodePath(node, "./"); // include all node path use <> to seperate
    std::vector<string> node_path = split(temp_path, "<>");

    int num = 0;  // judge if the name which the user want to search is bigger than 1
    for(int i = 0; i < allNode.size(); i++) {
      if(allNode[i] == name)
        num++;
    }

    Folder * folder = dynamic_cast<Folder *> (node); // down cast

    string ans;
    if(num == 0) {
      if(node->name() == name && folder == nullptr) {
        ans += name;
      }
      else {
        ans += "";
      }
    }
    else if (num == 1) {
      if(folder != nullptr) {
        Iterator * it = folder->createIterator();
        if(!it->isDone()) {
          for(it->first(); !it->isDone(); it->next()) {
            if(it->currentItem()->name() == name) {
              string leaf;
              leaf += allLeaf(it->currentItem());
              vector<string> temp_child = split(leaf, "<>");

              if(temp_child.size() > 1) {
                ans = temp_child[0];
                for(int j = 1; j < temp_child.size(); j++) {
                  ans += " ";
                  ans += temp_child[j];
                }
              }
              else {
                ans = "./" + name;
              }
            }
            else {  // recursively to find name
              ans += findNode(it->currentItem(), name);
            }
          }
        }
        else {
          ans += name;
        }
      }
      else {
        return ans += "";
      }
    }
    else if (num >= 2) {  // name have upper than one
      vector<string> multiple;
      for(int i = 0; i < allNode.size(); i++) {  // find all path with this name
        if(allNode[i] == name) {
          multiple.push_back(node_path[i]);
        }
      }
      ans += multiple[0];
      for(int i = 1; i < multiple.size(); i++) {
        ans += "\n";
        ans += multiple[i];
      }
    }
     return ans;
  }
};

//pratice here
int infoByte(Node* node) {
  int total = 0;
  Folder * folder = dynamic_cast<Folder *> (node); // down cast
  if (folder != nullptr) { //it's a folder
    Iterator * it = folder->createIterator();
    for(it->first(); !it->isDone(); it->next()){
      total += it->currentItem()->size();
    }
  }
  else{
    total+= node->size();
  }
  return total;
}

#endif
