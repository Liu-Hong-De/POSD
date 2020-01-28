#include "update_path_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node.h"
#include "iterator.h"

#include <vector>
#include <string>

using namespace std;

UpdatePathVisitor::UpdatePathVisitor() {

}

void UpdatePathVisitor::visitFolder(Folder * folder) {
  Iterator *it = folder->createIterator();

  for (it->first(); !it->isDone(); it->next()) {
    it->currentItem()->updateParentPath(folder->getPath());
    it->currentItem()->accept(this);
  }
}

void UpdatePathVisitor::visitFile(File * file) {
}

void UpdatePathVisitor::visitLink(Link * link) {
}
