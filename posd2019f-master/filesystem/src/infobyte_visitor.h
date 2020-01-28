#ifndef INFOBYTE_VISITOR
#define INFOBYTE_VISITOR

class File;
class Folder;

class InfoByteVisitor {
public:
  InfoByteVisitor();

  void visitFile(File * file);

  void visitFolder(Folder *folder);

  int total();
private:
  int _total;
};
#endif
