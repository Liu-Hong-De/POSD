#include <gtest/gtest.h>
#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/circular_sector.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"
#include <string>
#include <algorithm>

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST (ShapeTest, first)
{
  ASSERT_TRUE(true);
}

TEST (ShapeTest, Circle)
{
  Circle c(10.0);
  ASSERT_NEAR(314.159, c.area(), 0.001);
  ASSERT_NEAR(62.831, c.perimeter(), 0.001);
}

TEST (ShapeTest, CircularSector)
{
  CircularSector cs(10, 90);
  ASSERT_NEAR(78.539, cs.area(), 0.001);
  ASSERT_NEAR(35.707, cs.perimeter(), 0.001);
}

TEST (ShapeTest, Ellipse)
{
  Ellipse e(5, 2);
  ASSERT_NEAR(31.415, e.area(), 0.001);
  ASSERT_NEAR(24.566, e.perimeter(), 0.001);
}

TEST (ShapeTest, Rectangle)
{
  Rectangle r(3, 4);
  ASSERT_NEAR(12, r.area(), 0.001);
  ASSERT_NEAR(14, r.perimeter(), 0.001);
}

TEST (ShapeTest, Triangle)
{
  EXPECT_ANY_THROW(Triangle t(0, 0, 1, 0, 1, 0));
  EXPECT_ANY_THROW(Triangle t(0, 0, 1, 1, 2, 2));
  EXPECT_ANY_THROW(Triangle t(0, 0, 0, 2, 1, 0));
  Triangle t(0, 0, 0, 1, 1, 0);
  ASSERT_NEAR(0.5, t.area(), 0.001);
  ASSERT_NEAR(3.414, t.perimeter(),0.001);
}

TEST(ShapeTest, Sorting)
{
  Shape* test_array[10] = {new Circle(1.0), new Circle(0.5), new Rectangle(5, 6), new Rectangle(0.5, 1.5), new CircularSector(1, 180), new CircularSector(0.5, 180), new Ellipse(5, 2), new Ellipse(0.5, 0.2), new Triangle(0, 0, 0, 1, 1, 0), new Triangle(3, 4, 4, 5, 3, 6)};

  std::sort(test_array, test_array+10, [](Shape * a, Shape *b) {
    return a->area() < b->area();
  });
  ASSERT_NEAR(0.1*3.1415, test_array[0]->area(), 0.001);
  ASSERT_NEAR(0.25*3.1415*0.5, test_array[1]->area(), 0.001);
  ASSERT_NEAR(0.5, test_array[2]->area(), 0.001);
  ASSERT_NEAR(0.75, test_array[3]->area(), 0.001);
  ASSERT_NEAR(0.25*3.1415, test_array[4]->area(), 0.001);
  ASSERT_NEAR(1, test_array[5]->area(), 0.001);
  ASSERT_NEAR(0.5*3.1415, test_array[6]->area(), 0.001);
  ASSERT_NEAR(3.1415, test_array[7]->area(), 0.001);
  ASSERT_NEAR(30, test_array[8]->area(), 0.001);
  ASSERT_NEAR(10*3.1415, test_array[9]->area(), 0.001);
}
