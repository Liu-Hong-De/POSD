#ifndef FILE_H
#define FILE_H

#include <string>
#include <sys/stat.h>

#include "node.h"

class File: public Node {
public:
  File(std::string path): Node(path) {
    stat(path.c_str(), &_st);
    if(_st.st_mode & S_IFDIR) {
      throw(std::string("It is not File!"));
    }
  }

private:
  struct stat _st;
};

#endif
