#ifndef UT_FILE_H
#define UT_FILE_H

#include <sys/stat.h>

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/link.h"
#include "../src/utilities.h"
#include "../src/find_visitor.h"
#include "../src/visitor.h"
#include "../src/update_path_visitor.h"

class NodeTest : public ::testing::Test{
protected:
  void SetUp() {
    test = new Folder("test");
    hw = new Folder("test/hw");
    test_folder = new Folder("test/test_folder");
    F_out = new File("test/F.out");
    hw3 = new Folder("test/hw/hw3");
    c_out = new File("test/hw/c.out");
    hw_file = new File("test/hw/hw");
    c_cpp = new File("test/hw/hw3/c.cpp");
    test_folder_hw = new Folder("test/test_folder/hw");
    hw2 = new Folder("test/test_folder/hw2");
    hello_txt = new File("test/test_folder/hello.txt");
    hw1_cpp = new File("test/test_folder/hw1.cpp");
    hw2_h = new File("test/test_folder/hw2.h");
    hw_hw = new Folder("test/test_folder/hw/hw");
    a_out = new File("test/test_folder/hw/a.out");
    hw_hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
    hw1_link = new Link("test/test_folder/hw1", hw_hw1_cpp);
    // hw2_c_out = new File("test/test_folder/hw2/c.out");
    test->addChild(hw);
    test->addChild(test_folder);
    test->addChild(F_out);
    hw->addChild(c_out);
    hw->addChild(hw_file);
    hw->addChild(hw3);
    hw3->addChild(c_cpp);
    test_folder->addChild(hello_txt);
    test_folder->addChild(test_folder_hw);
    test_folder->addChild(hw2);
    test_folder->addChild(hw1_cpp);
    test_folder->addChild(hw2_h);
    test_folder->addChild(hw1_link);
    test_folder_hw->addChild(hw_hw);
    test_folder_hw->addChild(a_out);
    test_folder_hw->addChild(hw_hw1_cpp);
    // hw2->addChild(hw2_c_out);
  }
  void TearDown() {
    delete test;
    delete hw;
    delete test_folder;
    delete F_out;
    delete hw3;
    delete c_out;
    delete hw_file;
    delete c_cpp;
    delete test_folder_hw;
    delete hw2;
    delete hello_txt;
    delete hw1_cpp;
    delete hw2_h;
    delete hw_hw;
    delete a_out;
    delete hw_hw1_cpp;
    delete hw1_link;
    // delete hw2_c_out;
  }
  Folder* test;
  Folder* hw;
  Folder* test_folder;
  File* F_out;
  Folder* hw3;
  File* c_out;
  File* hw_file;
  File* c_cpp;
  Folder* test_folder_hw;
  Folder* hw2;
  File* hello_txt;
  File* hw1_cpp;
  File* hw2_h;
  Folder* hw_hw;
  File* a_out;
  File* hw_hw1_cpp;
  Link* hw1_link;
  // Node* hw2_c_out;
};

TEST(StatApi, GetSize) {
  struct stat st;
  ASSERT_EQ(0, stat("test/test_folder/hello.txt", &st));
  int size = st.st_size;
  ASSERT_EQ(0, size);
}


TEST_F(NodeTest, First) {
  ASSERT_EQ(0, hello_txt->size());
}

TEST_F(NodeTest, Second) {
  Iterator * it= test_folder->createIterator();
  ASSERT_EQ(4096, test_folder->size());
  it->first();
  ASSERT_EQ(0, it->currentItem()->size());
  it->next();
  ASSERT_EQ(4096, it->currentItem()->size());
}

TEST_F(NodeTest, AddException){
  ASSERT_ANY_THROW(hello_txt->addChild(test_folder));
}

TEST_F(NodeTest, CatchException){
  try{
    hello_txt->addChild(test_folder);
    ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("Invalid add!", s);
  }
}

TEST_F(NodeTest, InfoByteFunctionOnFile){
  ASSERT_EQ(0, infoByte(hello_txt));
}

TEST_F(NodeTest, InfoByteFunctionOnFolder){
  ASSERT_EQ(4096, infoByte(hw));
}

TEST_F(NodeTest, IteratorFromFolder) {
  Iterator * it = hw->createIterator();
  it->first(); // Initialize
  ASSERT_EQ(c_out, it->currentItem());
  it->next();
  ASSERT_EQ(hw_file, it->currentItem());
  it->next();
  ASSERT_EQ(hw3, it->currentItem());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(NodeTest, IteratorFromFile){
  Iterator* it= hello_txt->createIterator();
  ASSERT_TRUE(it->isDone());
}

TEST_F(NodeTest, NextIsNullIterator) {
  Iterator * it = hw->createIterator();
  it->first(); // Initialize
  ASSERT_EQ(c_out, it->currentItem());
  it->next();
  ASSERT_EQ(hw_file, it->currentItem());
  it->next();
  ASSERT_EQ(hw3, it->currentItem());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(NodeTest, NullIterator) {
  Iterator * it = a_out->createIterator();
  try{
    it->first();
    FAIL();
  }catch(std::string message) {
    ASSERT_EQ("no child member", message);
  }
  try{
    it->next();
    FAIL();
  }catch(std::string message) {
    ASSERT_EQ("no child member", message);
  }
  try{
    it->currentItem();
    FAIL();
  }catch(std::string message) {
    ASSERT_EQ("no child member", message);
  }
  ASSERT_EQ(true, it->isDone());
}


TEST_F(NodeTest, NodeTypeError) {
  try{   //If the Folder doesn't exist, you should throw string "It is not Folder!"
    new Folder("test/test_folder/hello.txt");
    FAIL();
  } catch(string message) {
    ASSERT_EQ("It is not Folder!", message);
  }

  try{   //If the File doesn't exist, you should throw string "It is not File!"
    new File("test/test_folder/hw");
    FAIL();
  } catch(string message) {
    ASSERT_EQ("It is not File!", message);
  }

  try{   //If the Link doesn't exist, you should throw string "It is not Link!"
    new Link("test/test_folder/hello.txt", a_out);
    FAIL();
  } catch(string message) {
    ASSERT_EQ("It is not Link!", message);
  }

  try{   //If the Link doesn't exist, you should throw string "It is not Link!"
    new File("test/123");
    FAIL();
  } catch(string message) {
    ASSERT_EQ("Node is not exist!", message);
  }
}

TEST_F(NodeTest, TestLink){
  ASSERT_EQ(hw_hw1_cpp, hw1_link->getSource());
}

TEST_F(NodeTest, ReuseFindVisitor) {
  FindVisitor * fv = new FindVisitor("hw");
  test_folder->accept(fv);
  ASSERT_EQ("./hw\n./hw/hw", fv->findResult());
  test->accept(fv);
  ASSERT_EQ("./hw\n./hw/hw\n./test_folder/hw\n./test_folder/hw/hw", fv->findResult());
  hw_hw->accept(fv);
  ASSERT_EQ("", fv->findResult());
  test_folder_hw->accept(fv);
  ASSERT_EQ("./hw", fv->findResult());
  hw->accept(fv);
  ASSERT_EQ("./hw", fv->findResult());
  hw2->accept(fv);
  ASSERT_EQ("", fv->findResult());
}

TEST_F(NodeTest, ReuseFileFindVisitor) {
  FindVisitor * fv = new FindVisitor("hw1.cpp");
  hw_hw1_cpp->accept(fv);
  ASSERT_EQ("hw1.cpp", fv->findResult());
  test_folder->accept(fv);
  ASSERT_EQ("./hw/hw1.cpp\n./hw1.cpp", fv->findResult());
  test->accept(fv);
  ASSERT_EQ("./test_folder/hw/hw1.cpp\n./test_folder/hw1.cpp", fv->findResult());
  hw->accept(fv);
  ASSERT_EQ("", fv->findResult());
  test_folder_hw->accept(fv);
  ASSERT_EQ("./hw1.cpp", fv->findResult());
}

TEST_F(NodeTest, FindMultipleFile) {
  FindVisitor * fv = new FindVisitor("hw");
  test_folder->accept(fv);
  ASSERT_EQ("./hw\n./hw/hw", fv->findResult());
}

TEST_F(NodeTest, FindMultipleSameNameNode) {
  FindVisitor * fv = new FindVisitor("hw");
  test->accept(fv);
  ASSERT_EQ("./hw\n./hw/hw\n./test_folder/hw\n./test_folder/hw/hw", fv->findResult());
}

TEST_F(NodeTest, FindMultipleFile2) {
  FindVisitor * fv = new FindVisitor("hw1.cpp");
  test->accept(fv);
  test_folder->accept(fv);
  ASSERT_EQ("./hw/hw1.cpp\n./hw1.cpp", fv->findResult());
}

TEST_F(NodeTest, FindFileItself) {
  FindVisitor * fv = new FindVisitor("hw1.cpp");
  // test_folder_hw->accept(fv);
  hw1_cpp->accept(fv);
  ASSERT_EQ("hw1.cpp", fv->findResult());
}

TEST_F(NodeTest, FindFolder) {
  FindVisitor * fv = new FindVisitor("hw2");
  test->accept(fv);
  ASSERT_EQ("./test_folder/hw2", fv->findResult());
}

TEST_F(NodeTest, FindFolder2) {
  FindVisitor * fv = new FindVisitor("test_folder");
  test->accept(fv);
  ASSERT_EQ("./test_folder", fv->findResult());
}

TEST_F(NodeTest, FindEmptyFolder) {
  FindVisitor * fv = new FindVisitor("hw");
  hw_hw->accept(fv);
  ASSERT_EQ("", fv->findResult());
}

TEST_F(NodeTest, FindFolderItself) {
  FindVisitor * fv = new FindVisitor("test_folder");
  test_folder->accept(fv);
  ASSERT_EQ("", fv->findResult());
}

TEST_F(NodeTest, FindFile) {
  FindVisitor * fv = new FindVisitor("hw2");
  test_folder->accept(fv);
  ASSERT_EQ("./hw2", fv->findResult());
}

TEST_F(NodeTest, FindFileNotExistInFolder) {
  FindVisitor * fv = new FindVisitor("hello.txt");
  test_folder_hw->accept(fv);
  ASSERT_EQ("", fv->findResult());
}

TEST_F(NodeTest, RenameFile) {
  struct stat _st;
  hw = new Folder("test/test_folder/hw");
  hw->renameNode("TA_file");
  ASSERT_EQ("test/test_folder/TA_file", hw->getPath()); // Check the node name in your own file system!
  hw->renameNode("hw");
}

TEST_F(NodeTest, RenameFolder) {
  UpdatePathVisitor * upv = new UpdatePathVisitor();
  test_folder_hw->renameNode("qaz");
  test_folder_hw->accept(upv);
  ASSERT_EQ("test/test_folder/qaz/a.out", a_out->getPath()); // Check the path of itself!
  test_folder_hw->renameNode("hw");
}
#endif
