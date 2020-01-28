#ifndef UTILITIES_H
#define UTILITIES_H

#include "node.h"
#include "folder.h"

void infoByteVisitFolder(Folder* folder, int &total);
void infoByteVisitFile(File* file, int &total);

//pratice here
int infoByte(Node* node) {
  int total = 0;
  Folder * folder = dynamic_cast<Folder *> (node); // down cast
  if (folder != nullptr) { //it's a folder
    infoByteVisitFolder(folder, total);
  }
  else{ // it's a file
    File * file = dynamic_cast<File *> (node);
    if (file != nullptr) {
      infoByteVisitFile(file, total);
    }
  }
  return total;
}

// int infoByte(Node *node) {
//   InfoByteVisitor ibv;
//   node->accept(ibv);
//   return ibv.total();
// }

void infoByteVisitFolder(Folder* folder, int &total) {
  Node::Iterator * it = folder->createIterator();
  for(it->first(); !it->isDone(); it->next()){
    total += it->currentItem()->size();
  }
}


void infoByteVisitFile(File* file, int &total) {
  total+= file->size();
}

#endif
