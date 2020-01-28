#ifndef FILE_H
#define FILE_H

#include <string>
#include <sys/stat.h>

#include "node.h"
#include "null_iterator.h"

class File: public Node {
public:
  File(std::string path): Node(path)
  {
    struct stat st;
    if (lstat(path.c_str(), &st) == 0 && !S_ISREG(st.st_mode)) { // 判斷是否存在且為file
      throw string("It is not File!");
    }
  }
  void accept(Visitor *ibv) {
    ibv->visitFile(this);
  }

  string fileOrNot() {
    return "file";
  }

  Iterator * createIterator() {
    return new NullIterator();
  }
};

#endif
