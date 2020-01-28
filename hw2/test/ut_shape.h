#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/circular_sector.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"

TEST (ShapeTest, Circle)
{
  Circle c(10.0);
  ASSERT_NEAR(314.159, c.area(), 0.001);
  ASSERT_NEAR(62.831, c.perimeter(), 0.001);
  ASSERT_NEAR(102643.885, c.sumOfSquares(), 0.001);
}

TEST (ShapeTest, CircularSector)
{
  CircularSector cs(10, 90);
  ASSERT_NEAR(78.539, cs.area(), 0.001);
  ASSERT_NEAR(35.707, cs.perimeter(), 0.001);
  ASSERT_NEAR(7443.561, cs.sumOfSquares(), 0.001);
}

TEST (ShapeTest, Ellipse)
{
  Ellipse e(5, 2);
  ASSERT_NEAR(31.415, e.area(), 0.001);
  ASSERT_NEAR(24.566, e.perimeter(), 0.001);
  ASSERT_NEAR(1590.467, e.sumOfSquares(), 0.001);
}

TEST (ShapeTest, Rectangle)
{
  Rectangle r(3, 4);
  ASSERT_NEAR(12, r.area(), 0.001);
  ASSERT_NEAR(14, r.perimeter(), 0.001);
  ASSERT_NEAR(340, r.sumOfSquares(), 0.001);
}

TEST (ShapeTest, Triangle)
{
  EXPECT_ANY_THROW(Triangle t(0, 0, 1, 0, 1, 0));
  EXPECT_ANY_THROW(Triangle t(0, 0, 1, 1, 2, 2));
  EXPECT_ANY_THROW(Triangle t(0, 0, 0, 2, 1, 0));
  Triangle t(0, 0, 0, 1, 1, 0);
  ASSERT_NEAR(0.5, t.area(), 0.001);
  ASSERT_NEAR(3.414, t.perimeter(),0.001);
  ASSERT_NEAR(11.906, t.sumOfSquares(),0.001);
}
