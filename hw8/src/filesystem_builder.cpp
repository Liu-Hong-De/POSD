#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#include "file.h"
#include "folder.h"
#include "link.h"
#include "filesystem_builder.h"

using namespace std;

FileSystemBuilder::FileSystemBuilder() {}

FileSystemBuilder* FileSystemBuilder::_instance = 0;

FileSystemBuilder * FileSystemBuilder::instance(){
  if(_instance == 0) {
    _instance = new FileSystemBuilder();
  }
  return _instance;
}

void FileSystemBuilder::build(string path){
  struct stat st;
  // 判斷第一層是file，folder，link
  if (lstat(path.c_str(), &st) == 0 && S_ISREG(st.st_mode)) {
    _root = new File(path);
  }

  else if (lstat(path.c_str(), &st) == 0 && S_ISLNK(st.st_mode)) {
    _root = new Link(path);
  }

  else if (lstat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
    DIR * root;
    struct dirent * dp;
    root = opendir(path.c_str());
    if(root == nullptr) {
      throw string("Not Exist");
    }
    _root = new Folder(path);

    while((dp = readdir(root)) != NULL) {
      if(string(dp->d_name) == ".") {   // 忽略.和..
        continue;
      }
      else if(string(dp->d_name) == "..") {
        continue;
      }

      if (dp->d_type == DT_REG) {
        Node * n = new File(string(path) + "/" + string(dp->d_name));
        _root->addChild(n);
      }
      else if (dp->d_type == DT_LNK) {
        Node * n = new Link(string(path) + "/" + string(dp->d_name));
        _root->addChild(n);
      }
      else if (dp->d_type == DT_DIR) {  // 找到folder的話則繼續向底下找
        FileSystemBuilder fsb;
        fsb.build(string(path) + "/" + string(dp->d_name));
        _root->addChild(fsb.getRoot());
      }
    }
    closedir(root);
  }
}

Node * FileSystemBuilder::getRoot(){
  return _root;
}
