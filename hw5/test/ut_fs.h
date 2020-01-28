#ifndef UT_FILE_H
#define UT_FILE_H

#include <sys/stat.h>

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/utilities.h"

using namespace std;

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
    // hw2_c_out = new File("test/test_folder/hw2/c.out");
    test->addChild(hw);
    test->addChild(test_folder);
    test->addChild(F_out);
    hw->addChild(hw3);
    hw->addChild(c_out);
    hw->addChild(hw_file);
    hw3->addChild(c_cpp);
    test_folder->addChild(test_folder_hw);
    test_folder->addChild(hw2);
    test_folder->addChild(hello_txt);
    test_folder->addChild(hw1_cpp);
    test_folder->addChild(hw2_h);
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
    // delete hw2_c_out;
  }
  Node* test;
  Node* hw;
  Node* test_folder;
  Node* F_out;
  Node* hw3;
  Node* c_out;
  Node* hw_file;
  Node* c_cpp;
  Node* test_folder_hw;
  Node* hw2;
  Node* hello_txt;
  Node* hw1_cpp;
  Node* hw2_h;
  Node* hw_hw;
  Node* a_out;
  Node* hw_hw1_cpp;
  // Node* hw2_c_out;
};

TEST(StatApi, GetSize) {
  struct stat st;
  ASSERT_EQ(0, stat("test/test_folder/hello.txt", &st));
  int size = st.st_size;
  ASSERT_EQ(14, size);
}


TEST_F(NodeTest, First) {
  ASSERT_EQ(14, hello_txt->size());
}

TEST_F(NodeTest, Second) {
  Iterator * it= test_folder->createIterator();
  ASSERT_EQ(4096, test_folder->size());
  it->first();
  ASSERT_EQ(14, it->currentItem()->size());
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
  ASSERT_EQ(14, infoByte(hello_txt));
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
  try{
    it->next();
    FAIL();
  }catch(std::string message) {
    ASSERT_EQ("Moving past the end!", message);
  }
  try{
    it->currentItem();
    FAIL();
  }catch(std::string message) {
    ASSERT_EQ("No current item!", message);
  }
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

TEST_F(NodeTest, ListNode) {
  Utilities utilities;
  ASSERT_EQ("c.out hw hw3", utilities.listNode(hw));
  try{
    utilities.listNode(a_out);
    FAIL();
  } catch(std::string message) {
    ASSERT_EQ("Not a directory", message);
  }
}

TEST_F(NodeTest, FindNode) {
  Utilities utilities;
  ASSERT_EQ("./hw\n./hw/hw", utilities.findNode(test_folder, "hw"));
  ASSERT_EQ("./hw\n./hw/hw\n./test_folder/hw\n./test_folder/hw/hw", utilities.findNode(test, "hw"));
  ASSERT_EQ("./hw/hw1.cpp\n./hw1.cpp", utilities.findNode(test_folder, "hw1.cpp"));
  ASSERT_EQ("hw1.cpp", utilities.findNode(hw1_cpp, "hw1.cpp"));
  ASSERT_EQ("hello.txt a.out hw1.cpp hw1.cpp hw2.h", utilities.findNode(test, "test_folder"));
  ASSERT_EQ("", utilities.findNode(hw_hw, "hw"));
  ASSERT_EQ("", utilities.findNode(test_folder, "test_folder"));
  ASSERT_EQ("./hw2", utilities.findNode(test_folder, "hw2"));
}

#endif
