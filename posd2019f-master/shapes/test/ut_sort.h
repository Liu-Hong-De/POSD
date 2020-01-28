#include <algorithm>
#include <math.h>

TEST(Sort, IntAscending){
  int a[] = {3, 2, 5, 6, 1, 8};
  std::sort(a, a+6);
  ASSERT_EQ(1, a[0]);
  ASSERT_EQ(2, a[1]);
  ASSERT_EQ(3, a[2]);
  ASSERT_EQ(5, a[3]);
  ASSERT_EQ(6, a[4]);
  ASSERT_EQ(8, a[5]);
}

bool greaterThan(int a, int b){
  return a > b;
}

TEST(Sort, IntDescending){
  int a[] = {3, 2, 5, 6, 1, 8};
  std::sort(a, a+6, greaterThan);
  ASSERT_EQ(8, a[0]);
  ASSERT_EQ(6, a[1]);
  ASSERT_EQ(5, a[2]);
  ASSERT_EQ(3, a[3]);
  ASSERT_EQ(2, a[4]);
  ASSERT_EQ(1, a[5]);
}

class GreaterThanObj{
public:
  bool operator()(int a, int b) {
    return a > b;
  }
};

TEST(Sort, IntDescendingWithObject){
  int a[] = {3, 2, 5, 6, 1, 8};
  GreaterThanObj greaterThanObj;
  std::sort(a, a+6, greaterThanObj);
  ASSERT_EQ(8, a[0]);
  ASSERT_EQ(6, a[1]);
  ASSERT_EQ(5, a[2]);
  ASSERT_EQ(3, a[3]);
  ASSERT_EQ(2, a[4]);
  ASSERT_EQ(1, a[5]);
}

TEST(Sort, IntDescendingWithLambda){
  int a[] = {3, 2, 5, 6, 1, 8};
  std::sort(a, a+6, [](int a, int b){ return a > b;});
  ASSERT_EQ(8, a[0]);
  ASSERT_EQ(6, a[1]);
  ASSERT_EQ(5, a[2]);
  ASSERT_EQ(3, a[3]);
  ASSERT_EQ(2, a[4]);
  ASSERT_EQ(1, a[5]);
}

TEST(Sort, IntAscendingByDistanceToSix){
  int a[] = {3, 2, 5, 6, 1, 8};
  std::sort(a, a+6, [](int a, int b){
    return abs(6 - a) < abs(6 - b);
  });
  ASSERT_EQ(6, a[0]);
  ASSERT_EQ(5, a[1]);
  ASSERT_EQ(8, a[2]);
  ASSERT_EQ(3, a[3]);
  ASSERT_EQ(2, a[4]);
  ASSERT_EQ(1, a[5]);
}

class CompareDistanceByX{
public:
  CompareDistanceByX(int x){
    _x = x;
  }
  bool operator()(int a, int b){
    return abs(_x - a) < abs(_x - b);
  }
private:
  int _x;
};

TEST(Sort, IntAscendingByDistanceToX){
  int a[] = {3, 2, 5, 6, 1, 8};
  CompareDistanceByX compareDistanceByX(6);
  std::sort(a, a+6, compareDistanceByX);
  ASSERT_EQ(6, a[0]);
  ASSERT_EQ(5, a[1]);
  ASSERT_EQ(8, a[2]);
  ASSERT_EQ(3, a[3]);
  ASSERT_EQ(2, a[4]);
  ASSERT_EQ(1, a[5]);
}

TEST(Sort, IntAscendingByDistanceToXLambda){
  int a[] = {3, 2, 5, 6, 1, 8};
  int x = 6;
  std::sort(a, a+6, [x](int a, int b){
    return abs(x - a) < abs(x - b);
  });
  ASSERT_EQ(6, a[0]);
  ASSERT_EQ(5, a[1]);
  ASSERT_EQ(8, a[2]);
  ASSERT_EQ(3, a[3]);
  ASSERT_EQ(2, a[4]);
  ASSERT_EQ(1, a[5]);
}
