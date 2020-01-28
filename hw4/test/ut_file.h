#ifndef UT_FILE_H
#define UT_FILE_H

#include <sys/stat.h>

#include "../src/file.h"
#include "../src/folder.h"

TEST(StatApi, GetSize) {
  struct stat st;
  ASSERT_EQ(0, stat("test/test_folder/hello.txt", &st));
  int size = st.st_size;
  ASSERT_EQ(14, size);
}

TEST(FileTest, First) {
  File hello_txt("test/test_folder/hello.txt");
  ASSERT_EQ(14, hello_txt.size());
}

TEST(FileTest, Second) {
  File hello_txt("test/test_folder/hello.txt");
  Folder test_folder("test/test_folder");
  ASSERT_EQ(4096, test_folder.size());
  test_folder.addChild(&hello_txt);
  ASSERT_EQ(14, test_folder.getChild(0)->size());

  Folder hw("test/test_folder/hw");
  test_folder.addChild(&hw);
  ASSERT_EQ(4096, test_folder.getChild(1)->size());
}

TEST(FileTest, AddException){
  File hello_txt("test/test_folder/hello.txt");
  Folder test_folder("test/test_folder");
  ASSERT_ANY_THROW(hello_txt.addChild(&test_folder));
}

TEST(FileTest, CatchException){
  File hello_txt("test/test_folder/hello.txt");
  Folder test_folder("test/test_folder");
  try{
    hello_txt.addChild(&test_folder);
    ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("Invalid add!", s);
  }
}

TEST(FileTest, InfoByteOnFile){
  Node* hello_txt = new File("test/test_folder/hello.txt");
  ASSERT_EQ(14, hello_txt->infoByte());
}

TEST(FileTest, InfoByteOnFolder){
  Node* hw = new Folder("test/test_folder/hw");
  Node* a_out = new File("test/test_folder/hw/a.out");
  Node* hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
  hw->addChild(a_out);
  hw->addChild(hw1_cpp);
  ASSERT_EQ(19027, hw->infoByte());
}

TEST(FileTest, InfoByteFunctionOnFolder){
  Node* hw = new Folder("test/test_folder/hw");
  Node* a_out = new File("test/test_folder/hw/a.out");
  Node* hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
  hw->addChild(a_out);
  hw->addChild(hw1_cpp);
  ASSERT_EQ(19027, infoByte(hw));
}

TEST(FileTest, FakeFile){
  try{
    Node* hw = new File("test/test_folder/hw");
    FAIL();
  } catch(std::string s){
    ASSERT_EQ("It is not File!", s);
  }
}

TEST(FileTest, FakeFolder){
  try{
    Node* hw = new Folder("test/test_folder/hello.txt");
    FAIL();
  } catch(std::string s){
    ASSERT_EQ("It is not Folder!", s);
  }
}

TEST(FileTest, NotExist){
  try{
    Node* hw = new Folder("test/test_folder/hello.tssxt");
    FAIL();
  } catch(std::string s){
    ASSERT_EQ("Node is not exist!", s);
  }

  try{
    Node* hw = new File("test/test_folder/hello.tssxt");
    FAIL();
  } catch(std::string s){
    ASSERT_EQ("Node is not exist!", s);
  }
}

TEST(FileTest, FileName){
    Node* hw = new Folder("test/test_folder/hw");
    ASSERT_EQ("hw", hw->name());
    Node* hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
    ASSERT_EQ("hw1.cpp", hw1_cpp->name());
}

TEST(FileTest, FindFile){
    Node* hw = new Folder("test/test_folder/hw");
    Node* hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
    hw->addChild(hw1_cpp);
    ASSERT_EQ("hw1.cpp", hw1_cpp->name());
}

TEST(FileTest, FindFolder){
  Node* test = new Folder("test");
  Node* test_folder = new Folder("test/test_folder");
  test->addChild(test_folder);
  Node* hw = new Folder("test/test_folder/hw");
  Node* hw2_h = new File("test/test_folder/hw2.h");
  test_folder->addChild(hw);
  test_folder->addChild(hw2_h);
  Node* a_out = new File("test/test_folder/hw/a.out");
  Node* hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
  hw->addChild(a_out);
  hw->addChild(hw1_cpp);
  ASSERT_EQ("a.out hw1.cpp hw2.h", test->findNode("test_folder"));
  ASSERT_EQ("a.out hw1.cpp", test_folder->findNode("hw"));
}

TEST(FileTest, FindFolderItself){
    Node* test_folder = new Folder("test/test_folder");
    Node* hw = new Folder("test/test_folder/hw");
    Node* hw2_h = new File("test/test_folder/hw2.h");
    test_folder->addChild(hw);
    test_folder->addChild(hw2_h);
    ASSERT_EQ("", test_folder->findNode("test_folder"));
    ASSERT_EQ("./hw", test_folder->findNode("hw"));
}

TEST(FileTest, FindFolderTwoLayer){
  Node* test = new Folder("test");
  Node* test_folder = new Folder("test/test_folder");
  test->addChild(test_folder);
  Node* hw = new Folder("test/test_folder/hw");
  Node* hw2_h = new File("test/test_folder/hw2.h");
  test_folder->addChild(hw);
  test_folder->addChild(hw2_h);
  Node* a_out = new File("test/test_folder/hw/a.out");
  Node* hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
  hw->addChild(a_out);
  hw->addChild(hw1_cpp);
  ASSERT_EQ("a.out hw1.cpp", test->findNode("hw"));
}

TEST(FileTest, FindFileLayer){
  Node* test = new Folder("test");
  Node* test_folder = new Folder("test/test_folder");
  test->addChild(test_folder);
  Node* hw = new Folder("test/test_folder/hw");
  Node* hw2_h = new File("test/test_folder/hw2.h");
  test_folder->addChild(hw);
  test_folder->addChild(hw2_h);
  Node* a_out = new File("test/test_folder/hw/a.out");
  Node* hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
  hw->addChild(a_out);
  hw->addChild(hw1_cpp);
  ASSERT_EQ("./a.out", test->findNode("a.out"));
}

TEST(FileTest, FindFileInFolder){
  Node* test = new Folder("test");
  Node* test_folder = new Folder("test/test_folder");
  test->addChild(test_folder);
  Node* hw = new Folder("test/test_folder/hw");
  Node* hw2_h = new File("test/test_folder/hw2.h");
  test_folder->addChild(hw);
  test_folder->addChild(hw2_h);
  Node* a_out = new File("test/test_folder/hw/a.out");
  Node* hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
  hw->addChild(a_out);
  hw->addChild(hw1_cpp);
  ASSERT_EQ("./a.out", test->findNode("a.out"));
}

TEST(FileTest, SameNameFile){
  Node* test_folder = new Folder("test/test_folder");
  Node* hw = new Folder("test/test_folder/hw");
  Node* hw1_cpp = new File("test/test_folder/hw1.cpp");
  test_folder->addChild(hw);
  test_folder->addChild(hw1_cpp);
  Node* a_out = new File("test/test_folder/hw/a.out");
  Node* hw1__cpp = new File("test/test_folder/hw/hw1.cpp");
  hw->addChild(a_out);
  hw->addChild(hw1__cpp);
  ASSERT_EQ("./hw/hw1.cpp\n./hw1.cpp", test_folder->findNode("hw1.cpp"));
}

TEST(FileTest, SameNameFolderInFolder){
  Node* test_folder = new Folder("test/test_folder");
  Node* hw = new Folder("test/test_folder/hw");
  Node* hw1_cpp = new File("test/test_folder/hw1.cpp");
  test_folder->addChild(hw);
  test_folder->addChild(hw1_cpp);
  Node* a_out = new File("test/test_folder/hw/a.out");
  Node* hw_hw1__cpp = new File("test/test_folder/hw/hw1.cpp");
  Node* hw_in_hw = new Folder("test/test_folder/hw/hw");
  hw->addChild(hw_in_hw);
  hw->addChild(a_out);
  hw->addChild(hw_hw1__cpp);
  ASSERT_EQ("./hw", hw->findNode("hw"));
}

TEST(FileTest, SameNameFolder){
  Node* test = new Folder("test");
  Node* test_folder = new Folder("test/test_folder");
  Node* hw_hw = new Folder("test/hw");
  test->addChild(test_folder);
  test->addChild(hw_hw);
  Node* hw = new Folder("test/test_folder/hw");
  Node* hw1_cpp = new File("test/test_folder/hw1.cpp");
  test_folder->addChild(hw);
  test_folder->addChild(hw1_cpp);
  Node* a_out = new File("test/test_folder/hw/a.out");
  Node* hw1__cpp = new File("test/test_folder/hw/hw1.cpp");
  hw->addChild(a_out);
  hw->addChild(hw1__cpp);
  ASSERT_EQ("./test_folder/hw\n./hw", test->findNode("hw"));
}

TEST(FileTest, ListNode){
  Node* test = new Folder("test");
  Node* hw = new Folder("test/hw");
  Node* test_folder = new Folder("test/test_folder");
  Node* F_out = new File("test/F.out");
  test->addChild(test_folder);
  test->addChild(F_out);
  test->addChild(hw);
  ASSERT_EQ("F.out hw test_folder", test->listNode());
  try{
    ASSERT_EQ("", F_out->listNode());
    FAIL();
  } catch(std::string s){
    ASSERT_EQ("Not a directory", s);
  }
  ASSERT_EQ("", hw->listNode());
}

#endif
