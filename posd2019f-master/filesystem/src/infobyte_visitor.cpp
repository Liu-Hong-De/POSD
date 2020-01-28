#include "infobyte_visitor.h"
#include "file.h"
#include "folder.h"

InfoByteVisitor::InfoByteVisitor(): _total(0){}

void InfoByteVisitor::visitFile(File * file) {
  _total += file->size();
}

void InfoByteVisitor::visitFolder(Folder *folder) {
  Node::Iterator *it = folder->createIterator();
  for (it->first(); !it->isDone(); it->next()) {
    it->currentItem()->accept(*this);
  }
}

int InfoByteVisitor::total() {
  return _total;
}
