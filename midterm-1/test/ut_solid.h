#include <gtest/gtest.h>
#include "../src/solid.h"
#include "../src/cone.h"
#include "../src/square_cylinder.h"
#include "../src/triangular_pyramid.h"
#include "../src/complex_solids.h"
#include <vector>
#include <iostream>

using namespace std;

TEST (SolidTest, TriangularPyramidCalculate)
{
  // 2 points
  // Test bottomArea() and volume() of TriangularPyramid
  TriangularPyramid tp(0, 0, 0, 1, 1, 0, 6);
  ASSERT_NEAR(0.5, tp.bottomArea(), 0.001);
  ASSERT_NEAR(1, tp.volume(), 0.001);

  try {
    TriangularPyramid tp(0, 0, 0, 1, 1, 0, 6);
  } catch(std::string message) {
    ASSERT_EQ("Bottom is not a Triangle!", message);
  }
}

TEST (SolidTest, ConeCalculate)
{
  // 2 points
  // Test bottomArea() and volume() of Cone
  Cone c(1, 0, 3, 0, 2);
  ASSERT_NEAR(3.141, c.bottomArea(), 0.001);
  ASSERT_NEAR(2.094, c.volume(), 0.001);

  try{
    Cone c_throw(1, 0, 1, 0, 1);
    FAIL();
  } catch(std::string message) {
    ASSERT_EQ("Bottom is not a Circle!", message);
  }
}

TEST (SolidTest, SquareCylinderCaculate)
{
  // 2 points
  // Test bottomArea() and volume() of SquareCylinder
  SquareCylinder sc(2, 5);
  ASSERT_NEAR(4, sc.bottomArea(), 0.001);
  ASSERT_NEAR(20, sc.volume(), 0.001);
}

TEST (SolidTest, ComplexSolidsTest)
{
  // 2 points
  // Test numberOfChild of ComplexSolids
  std::vector<Solid*>* shapes = new std::vector<Solid*>
   {
     new SquareCylinder(2, 5)
   };

   ComplexSolids* solid = new ComplexSolids(shapes);
   Solid* c = new Cone(1, 0, 3, 0, 2);
   solid->add(c);
   ASSERT_NEAR(3.141, (*shapes)[1]->bottomArea(), 0.001);

   ASSERT_EQ(2, solid->numberOfChild());
}

TEST (SolidTest, ComplexSolidsCalculate)
{
  // 2 points
  // Test bottomArea() and volume() of ComplexSolids
  std::vector<Solid*>* shapes = new std::vector<Solid*>
   {
     new SquareCylinder(2, 5),
     new Cone(1, 0, 3, 0, 2)
   };
   ComplexSolids* solid = new ComplexSolids(shapes);
   ASSERT_NEAR(7.141, solid->bottomArea(), 0.001);

   ASSERT_NEAR(22.094, solid->volume(), 0.001);
}


TEST (SolidTest, findBySolid){
  // 5 points
  // Test find() method of cone and TriangularPyramid and SquareCylinder
}

TEST (SolidTest, findByComplextSolids){
  // 5 points
  // Test find() method of ComplexSolids
}
