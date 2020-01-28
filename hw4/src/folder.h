#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <sys/stat.h>
#include <vector>
#include <iostream>

#include "node.h"

using namespace std;

class Folder: public Node {
public:
  Folder(std::string path): Node(path) {
    stat(path.c_str(), &_st);
    if(_st.st_mode & S_IFREG) {
      throw(std::string("It is not Folder!"));
    }
  }

  void addChild(Node* child) {
    _v.push_back(child);
  }

  Node* getChild(int num) {
    if(!_v.empty()) {
      return _v[num];
    }
    else {
      return NULL;
    }
  }

  int infoByte() {
    int total = 0;
    for(int i = 0; i < _v.size(); i++){
      total += _v.at(i)->infoByte();
    }
    return total;
  }

  string allNode() {  // find which nodes under this folder
    string temp;
    if(!_v.empty()) {
      for(int i = 0; i < _v.size(); i++) {
        temp += _v[i]->name();
        temp += "<>";
        if(_v[i]->getChild(0) != NULL) {  // if has next layer, go to next layer
          temp += _v[i]->allNode();
        }
      }
    }
    return temp;
  }

  string allLeaf() {  // when find only one folder，find all leaves under this folder
    string temp;
    if(!_v.empty()) {
      for(int i = 0; i < _v.size(); i++) {
        if(_v[i]->getChild(0) != NULL) {
          temp += _v[i]->allLeaf();
        }
        else {
          temp += _v[i]->name();
          temp += "<>";
        }
      }
    }
    return temp;
  }

  string allNodePath(string begin) {  // find all nodes path which are under the folder you want to find
    string temp;
    if(!_v.empty()) {
      for(int i = 0; i < _v.size(); i++) {
        string child = "";
        temp += begin;
        temp += _v[i]->name();
        child += begin;
        child += _v[i]->name();
        temp += "<>";
        if(_v[i]->getChild(0) != NULL) {
          child += "/";
          temp += _v[i]->allNodePath(child);
        }
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

  string findNode(std::string name)
  {
    string temp = allNode(); // include all node string use <> to seperate
    std::vector<string> node = split(temp, "<>"); // because the file or folder name can not have <>

    string temp_path = allNodePath("./"); // include all node path use <> to seperate
    std::vector<string> node_path = split(temp_path, "<>");

    int count = 0;  // judge if the name which the user want to search is bigger than 1
    for(int i = 0; i < node.size(); i++) {
      if(node[i] == name)
        count++;
    }

    string ans;
    if (count == 1) {
      if(!_v.empty()) {
        for(int i = 0; i < _v.size(); i++) {
          if(_v[i]->name() == name) {
            string leaf;
            if(_v[i]->getChild(0) == NULL) {  // name is _v[i]
              ans += "./";
              ans += name;
            }
            else {  // name is folder
              leaf += _v[i]->allLeaf();
              vector<string> temp_child = split(leaf, "<>");
              ans = temp_child[0];
              for(int j = 1; j < temp_child.size(); j++) {
                ans += " ";
                ans += temp_child[j];
              }
            }
            break;  // find name success，breaf for loop
          }
          else {  // recursively to find name
            if(_v[i]->getChild(0) != NULL) {
              ans += _v[i]->findNode(name);
            }
          }
        }
      }
      else {
        return ans += "";
      }
    }
    else if (count >= 2) {  // name have upper than one
      vector<string> multiple;
      for(int i = 0; i < node.size(); i++) {  // find all path with this name
        if(node[i] == name) {
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

  string listNode()
{
      // implementation list child Node and Sort by dictionary
      // Result should be separated by space
      // For example:
      // Folder contains childnode "a.out" and "TA_folder" and "hello.txt"
      // It should return "TA_folder a.out hello.txt"
      // If node is file, it can't listNode.
      // It should throw "Not a directory"
      // For Example: TA_file->listNode()
      string list;
      vector<string> temp;
      if(!_v.empty()) {
        for(int i = 0; i < _v.size(); i++) {
          temp.push_back(_v[i]->name());
        }
        sort(temp.begin(), temp.end());
        list = temp[0];
        for(int i = 1; i < temp.size(); i++) {
          list += " ";
          list += temp[i];
        }
      }

      return list;
}

private:
  vector<Node*> _v;
  struct stat _st;
};

#endif
