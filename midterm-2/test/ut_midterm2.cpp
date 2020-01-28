#include <gtest/gtest.h>

#include "../src/integer.h"
#include "../src/set.h"
#include "../src/flattened_set_visitor.h"
#include "../src/visitor.h"

using namespace std;

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Midterm2, IntegerAdd) {
  Integer i1(1);
  Integer i2(2);
  try {
    i1.add(&i2);
    FAIL();
  } catch(string message) {
    ASSERT_EQ("It's an integer!", message);
  }
}

TEST(Midterm2, IntegerSize) {
  Integer i1(1);
  ASSERT_EQ(1, i1.size());
}

TEST(Midterm2, IntegerToString) {
  Integer i1(2);
  ASSERT_EQ("2", i1.toString());
}

TEST(Midterm2, IntegerSetOperator) {
  Integer i1(2);
  try {
    i1.setOperator('+');
    FAIL();
  } catch(string message) {
    ASSERT_EQ("Cannot set operator on it!", message);
  }
}

TEST(Midterm2, SetSize) {
  Integer i2(2);
  Set set;
  Integer integer(1);
  set.add(&i2);
  ASSERT_EQ(1, set.size());
}

TEST(Midterm2, SetToString) {
  Integer i1(1);
  Integer i2(2);
  Integer i3(3);
  Integer i4(4);
  Integer i5(5);
  Set set;
  Set set1;
  Set set2;
  Set set3;
  Set set4;
  set.add(&i1);
  set1.add(&i2);
  set.add(&set1);
  set2.add(&i3);
  set2.add(&i4);
  set3.add(&i5);
  set3.add(&set4);
  set2.add(&set3);
  set.add(&set2);
  ASSERT_EQ("{1,{2},{3,4,{5,{}}}}", set.toString());
}

TEST(Midterm2, Flattened_set_visitor) {
  Integer i1(1);
  Integer i2(2);
  Integer i3(3);
  Integer i4(4);
  Integer i5(5);
  Set set;
  Set set1;
  Set set2;
  Set set3;
  Set set4;
  set.add(&i1);
  set1.add(&i2);
  set.add(&set1);
  set2.add(&i3);
  set2.add(&i4);
  set3.add(&i5);
  set3.add(&set4);
  set2.add(&set3);
  set.add(&set2);
  FlattenedSetVisitor *fv;
  // i1.accept(fv);
  // ASSERT_EQ(1, fv->getResult()->size());
}
