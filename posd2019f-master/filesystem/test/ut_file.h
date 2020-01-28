#ifndef UT_FILE_H
#define UT_FILE_H

#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/utilities.h"
#include "../src/filesystem_builder.h"

class NodeTest : public ::testing::Test{
protected:
  void SetUp() {
    hw = new Folder("test/test_folder/hw");
    a_out = new File("test/test_folder/hw/a.out");
    hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
    hello_txt= new File("test/test_folder/hello.txt");
    test_folder= new Folder("test/test_folder");
    hw->addChild(a_out);
    hw->addChild(hw1_cpp);
    test_folder->addChild(hello_txt);
    test_folder->addChild(hw);
  }
  void TearDown() {
    delete hw;
    delete a_out;
    delete hw1_cpp;
    delete hello_txt;
    delete test_folder;
  }
  Folder* hw;
  Node* a_out;
  Node* hw1_cpp;
  File* hello_txt;
  Node* test_folder;
};

TEST(CApi, GetSize) {
  struct stat st;
  ASSERT_EQ(0, stat("test/test_folder/hello.txt", &st));
  int size = st.st_size;
  ASSERT_EQ(14, size);
}

TEST(CApi, readlink) {
  char buf[1024];
  ssize_t len;
  if ((len = readlink("test/test_folder/hello", buf, sizeof(buf)-1)) != -1)
      buf[len] = '\0';
  ASSERT_EQ(8, len);
  ASSERT_EQ(std::string("hw/a.out"), buf);
}

TEST(CApi, opendir) {
  DIR *dir;
  dir = opendir("./not_exist");
  ASSERT_EQ(nullptr, dir);
  dir = opendir ("./test/test_folder");
  ASSERT_NE(nullptr, dir);

  struct dirent *dp;
  dp = readdir(dir);
  ASSERT_EQ(std::string("."), dp->d_name);
  dp = readdir(dir);
  ASSERT_EQ(std::string(".."), dp->d_name);
  dp = readdir(dir);
  ASSERT_EQ(std::string("hw"), dp->d_name);
  dp = readdir(dir);
  ASSERT_EQ(std::string("hwlink"), dp->d_name);
  dp = readdir(dir);
  ASSERT_EQ(std::string("hellolink"), dp->d_name);
  dp = readdir(dir);
  ASSERT_EQ(std::string("hello"), dp->d_name);
  dp = readdir(dir);
  ASSERT_EQ(std::string("hello.txt"), dp->d_name);
}

TEST_F(NodeTest, First) {
  ASSERT_EQ(14, hello_txt->size());
}

TEST_F(NodeTest, Second) {
  Node::Iterator * it= test_folder->createIterator();
  ASSERT_EQ(224, test_folder->size());
  it->first();
  ASSERT_EQ(14, it->currentItem()->size());
  it->next();
  ASSERT_EQ(128, it->currentItem()->size());
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
  ASSERT_EQ(19027, infoByte(hw));
}

TEST_F(NodeTest, IteratorFromFolder) {
  Node::Iterator * it = hw->createIterator();
  it->first(); // Initialize
  ASSERT_EQ(a_out, it->currentItem());
  it->next();
  ASSERT_EQ(hw1_cpp, it->currentItem());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(NodeTest, IteratorFromFile){
  Node::Iterator* it= hello_txt->createIterator();
  ASSERT_TRUE(it->isDone());
}

TEST_F(NodeTest, InfoByteVisitorOnFile) {
  InfoByteVisitor ibv;
  hello_txt->accept(ibv);
  ASSERT_EQ(14, ibv.total());
}

TEST_F(NodeTest, InfoByteVisitorOnFolder) {
  InfoByteVisitor ibv;
  hw->accept(ibv);
  ASSERT_EQ(19027, ibv.total());
}

TEST_F(NodeTest, InfoByteVisitorOnTestFolder) {
  InfoByteVisitor ibv;
  test_folder->accept(ibv);
  ASSERT_EQ(19041, ibv.total());
}

TEST(BuilderTest, BuildRoot) {
  FileSystemBuilder fsb;
  fsb.build("./test/test_folder");
  Node *n = fsb.getRoot();
  ASSERT_EQ(224, n->size());
}

TEST(BuilderTest, BuildRootFail) {
  FileSystemBuilder fsb;
  ASSERT_ANY_THROW(fsb.build("./not_exist"));
}

TEST(BuilderTest, CreateNodes) {
  FileSystemBuilder fsb;
  fsb.build("./test/test_folder/hw");
  Node * hw = fsb.getRoot();
  Node::Iterator * it = hw->createIterator();
  it -> first();
  ASSERT_EQ(119, it->currentItem()->size());
  it -> next();
  ASSERT_EQ(18908, it->currentItem()->size());
  it -> next();
  ASSERT_TRUE(it->isDone());
}

#endif
