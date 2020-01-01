# Pattern Oriented Software Design
#### Fall, 2019
#### Dept. of Computer Science and Information Engineering
#### Taipei Tech

#### Homework 7

# Purpose of the homework

####  Use the [course material](https://ssl-gitlab.csie.ntut.edu.tw/yccheng/posd2019f) to implement FileSystemBuilder and verify the node is created correctly by builder.

### practice Singleton pattern.

# Requirements
 1. You can reference [course project directory](https://ssl-gitlab.csie.ntut.edu.tw/yccheng/posd2019f).
 
 2. Throwing an exception as hw6 if your path of constructor does not correspond with your class or the node doesn't exist.

        TEST (FileSystemTest, NodeTypeError)
        {
          ASSERT_ANY_THROW(new File("./123")); //If the node doesn't exist, you should throw string "Node is not exist!"
          ASSERT_ANY_THROW(new File("./test_data/folder")); //If the File doesn't exist, you should throw string "It is not File!"
          ASSERT_ANY_THROW(new Folder("./test_data/hello")); //If the Folder doesn't exist, you should throw string "It is not Folder!"
          ASSERT_ANY_THROW(new Link("./test_data/test")); //If the Link doesn't exist, you should throw string "It is not Link!"
        }

 3. Link class will have nullptr as default target if you didn't give it target in constructor.

 4. Creat FileSystemBuilder class in `filesystem_builder.h` and implement it in `filesystem_builder.cpp`. The interface of FileSystemBuilder is as follows:
 

        class FileSystemBuilder  {
            protected:
                FileSystemBuilder();
            public:
                static FileSystemBuilder * instance();
                void build(string path);
                Node * getRoot();
        }
        
 5. Apply Singleton pattern on FileSystemBuilder. This means you will access the same FileSystemBuilder each time.        

 6. TA will write test cases to verify the builder can build the correct object.

        TEST(FileSystemBuilder, file){
          FileSystemBuilder * fb = FileSystemBuilder::instance();
          fb.build("test/test_folder/a.out");
          ASSERT_EQ("a.out", fb.getRoot()->name());
          ASSERT_EQ("test/test_folder/a.out", fb.getRoot()->getPath());
        }

 7. Use `std::map` in folder and take name of node as key of map to make sure the sequence in folder is the same as TA.
 
 8. You don't have to let Link class to point to the target in builder. 

 9. Write the corresponding makefile to generate executable file which named `ut_all` in bin folder.

# Grading rubrics

TA assigned 8 test cases in CI.

# Deadline
11:59 p.m. 11 Dec 2019

# Note
`ut_main.cpp` should include "ut_fs.h"

```
- bin
    - ut_all
- obj
    - filesystem_builder.o
- src
    - file.h
    - filesystem_builder.cpp
    - filesystem_builder.h
    - folder.h
    - iterator.h
    - link.h
    - node.h
    - null_iterator.h
    - visitor.h
- test
    - test_folder
    - ut_fs.h
    - ut_main.cpp
makefile
```
1. Make sure your all tests pass on your local machine. 
Then you can push to Gitlab and see the report on Jenkins.