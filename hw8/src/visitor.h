#ifndef VISITOR_H
#define VISITOR_H

class File;
class Folder;
class Link;

#include <string>

using namespace std;

class Visitor {
public:
  virtual void visitFile(File * file) = 0;
  virtual void visitFolder(Folder *folder) = 0;
  virtual void visitLink(Link *link) = 0;
};
#endif
