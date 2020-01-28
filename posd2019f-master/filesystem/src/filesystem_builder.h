#ifndef FILESYSTEM_BUILDER_H
#define FILESYSTEM_BUILDER_H

#include <string>

#include "folder.h"

class FileSystemBuilder {
public:
  void build(std::string path) {
    DIR * root;
    root = opendir(path.c_str());
    if (root == nullptr) {
      throw std::string("Not Exist");
    }
    _root = new Folder(path);
    struct dirent * dp;
    while((dp = readdir(root)) != NULL) {
      if (dp->d_type == DT_REG) {
        Node * n = new File(std::string(path) + "/" + std::string(dp->d_name));
        _root->addChild(n);
      }
    }
  }

  Node * getRoot() {
    return _root;
  }

private:
  Node * _root;
};
#endif
