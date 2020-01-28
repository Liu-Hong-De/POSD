#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/circular_sector.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"
#include "../src/sort.h"

TEST (ShapeTest, AreaAscendingSortOperator)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   AscendingComparison ascendingComparison("area");
   sort->sortArea(ascendingComparison);

   ASSERT_NEAR(0.75, (*shapes)[0]->area(), 0.001);
   ASSERT_NEAR(0.25*3.1415, (*shapes)[1]->area(), 0.001);
   ASSERT_NEAR(3.1415, (*shapes)[2]->area(), 0.001);
   ASSERT_NEAR(30, (*shapes)[3]->area(), 0.001);
}

TEST (ShapeTest, AreaDescendingSortOperator)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   DescendingComparison descendingComparison("area");
   sort->sortArea(descendingComparison);

   ASSERT_NEAR(0.75, (*shapes)[3]->area(), 0.001);
   ASSERT_NEAR(0.25*3.1415, (*shapes)[2]->area(), 0.001);
   ASSERT_NEAR(3.1415, (*shapes)[1]->area(), 0.001);
   ASSERT_NEAR(30, (*shapes)[0]->area(), 0.001);
}

TEST (ShapeTest, AreaAscendingSortLambda)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   sort->sortArea([](Shape* a, Shape* b)
   {
     return a->area() < b->area();
   });

   ASSERT_NEAR(0.75, (*shapes)[0]->area(), 0.001);
   ASSERT_NEAR(0.25*3.1415, (*shapes)[1]->area(), 0.001);
   ASSERT_NEAR(3.1415, (*shapes)[2]->area(), 0.001);
   ASSERT_NEAR(30, (*shapes)[3]->area(), 0.001);
}

TEST (ShapeTest, AreaDescendingSortLambda)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   sort->sortArea([](Shape* a, Shape* b)
   {
     return a->area() > b->area();
   });

   ASSERT_NEAR(0.75, (*shapes)[3]->area(), 0.001);
   ASSERT_NEAR(0.25*3.1415, (*shapes)[2]->area(), 0.001);
   ASSERT_NEAR(3.1415, (*shapes)[1]->area(), 0.001);
   ASSERT_NEAR(30, (*shapes)[0]->area(), 0.001);
}

TEST (ShapeTest, AreaAscendingSortFunction)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   sort->sortArea(areaAscendingComparison);

   ASSERT_NEAR(0.75, (*shapes)[0]->area(), 0.001);
   ASSERT_NEAR(0.25*3.1415, (*shapes)[1]->area(), 0.001);
   ASSERT_NEAR(3.1415, (*shapes)[2]->area(), 0.001);
   ASSERT_NEAR(30, (*shapes)[3]->area(), 0.001);
}

TEST (ShapeTest, AreaDescendingSortFunction)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   sort->sortArea(areaDescendingComparison);

   ASSERT_NEAR(0.75, (*shapes)[3]->area(), 0.001);
   ASSERT_NEAR(0.25*3.1415, (*shapes)[2]->area(), 0.001);
   ASSERT_NEAR(3.1415, (*shapes)[1]->area(), 0.001);
   ASSERT_NEAR(30, (*shapes)[0]->area(), 0.001);
}

TEST (ShapeTest, PerimeterAscendingSortLambda)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   sort->sortPerimeter([](Shape* a, Shape* b)
   {
     return a->perimeter() < b->perimeter();
   });

   ASSERT_NEAR(3.1415, (*shapes)[0]->perimeter(), 0.001);
   ASSERT_NEAR(4, (*shapes)[1]->perimeter(), 0.001);
   ASSERT_NEAR(2*3.1415, (*shapes)[2]->perimeter(), 0.001);
   ASSERT_NEAR(22, (*shapes)[3]->perimeter(), 0.001);
}

TEST (ShapeTest, PerimeterDescendingSortLambda)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   sort->sortPerimeter([](Shape* a, Shape* b)
   {
     return a->perimeter() > b->perimeter();
   });

   ASSERT_NEAR(3.1415, (*shapes)[3]->perimeter(), 0.001);
   ASSERT_NEAR(4, (*shapes)[2]->perimeter(), 0.001);
   ASSERT_NEAR(2*3.1415, (*shapes)[1]->perimeter(), 0.001);
   ASSERT_NEAR(22, (*shapes)[0]->perimeter(), 0.001);
}

TEST (ShapeTest, PerimeterAscendingSortOperator)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   AscendingComparison ascendingComparison("perimeter");
   sort->sortPerimeter(ascendingComparison);

   ASSERT_NEAR(3.1415, (*shapes)[0]->perimeter(), 0.001);
   ASSERT_NEAR(4, (*shapes)[1]->perimeter(), 0.001);
   ASSERT_NEAR(2*3.1415, (*shapes)[2]->perimeter(), 0.001);
   ASSERT_NEAR(22, (*shapes)[3]->perimeter(), 0.001);
}

TEST (ShapeTest, PerimeterDescendingSortOperator)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   DescendingComparison descendingComparison("perimeter");
   sort->sortPerimeter(descendingComparison);

   ASSERT_NEAR(3.1415, (*shapes)[3]->perimeter(), 0.001);
   ASSERT_NEAR(4, (*shapes)[2]->perimeter(), 0.001);
   ASSERT_NEAR(2*3.1415, (*shapes)[1]->perimeter(), 0.001);
   ASSERT_NEAR(22, (*shapes)[0]->perimeter(), 0.001);
}

TEST (ShapeTest, SumOfSquaresAscendingSortOperator)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   AscendingComparison ascendingComparison("sumOfSquares");
   sort->sortPerimeter(ascendingComparison);

   ASSERT_NEAR(10.4864, (*shapes)[0]->sumOfSquares(), 0.001);
   ASSERT_NEAR(16.5625, (*shapes)[1]->sumOfSquares(), 0.001);
   ASSERT_NEAR(49.348, (*shapes)[2]->sumOfSquares(), 0.001);
   ASSERT_NEAR(1384, (*shapes)[3]->sumOfSquares(), 0.001);
}

TEST (ShapeTest, SumOfSquaresDescendingSortOperator)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   DescendingComparison descendingComparison("sumOfSquares");
   sort->sortPerimeter(descendingComparison);

   ASSERT_NEAR(10.4864, (*shapes)[3]->sumOfSquares(), 0.001);
   ASSERT_NEAR(16.5625, (*shapes)[2]->sumOfSquares(), 0.001);
   ASSERT_NEAR(49.348, (*shapes)[1]->sumOfSquares(), 0.001);
   ASSERT_NEAR(1384, (*shapes)[0]->sumOfSquares(), 0.001);
}

TEST (ShapeTest, SumOfSquaresAscendingSortLambda)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   sort->sortSumOfSquares([](Shape* a, Shape* b)
   {
     return a->sumOfSquares() < b->sumOfSquares();
   });

   ASSERT_NEAR(10.4864, (*shapes)[0]->sumOfSquares(), 0.001);
   ASSERT_NEAR(16.5625, (*shapes)[1]->sumOfSquares(), 0.001);
   ASSERT_NEAR(49.348, (*shapes)[2]->sumOfSquares(), 0.001);
   ASSERT_NEAR(1384, (*shapes)[3]->sumOfSquares(), 0.001);
}

TEST (ShapeTest, SumOfSquaresDescendingSortLambda)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   sort->sortSumOfSquares([](Shape* a, Shape* b)
   {
     return a->sumOfSquares() > b->sumOfSquares();
   });

   ASSERT_NEAR(10.4864, (*shapes)[3]->sumOfSquares(), 0.001);
   ASSERT_NEAR(16.5625, (*shapes)[2]->sumOfSquares(), 0.001);
   ASSERT_NEAR(49.348, (*shapes)[1]->sumOfSquares(), 0.001);
   ASSERT_NEAR(1384, (*shapes)[0]->sumOfSquares(), 0.001);
}

TEST (ShapeTest, QuickSortLambda)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   sort->quickSort([](Shape* a, Shape* b)
    {
        return a->sumOfSquares() < b->sumOfSquares();
    });

   ASSERT_NEAR(10.4864, (*shapes)[0]->sumOfSquares(), 0.001);
   ASSERT_NEAR(16.5625, (*shapes)[1]->sumOfSquares(), 0.001);
   ASSERT_NEAR(49.348, (*shapes)[2]->sumOfSquares(), 0.001);
   ASSERT_NEAR(1384, (*shapes)[3]->sumOfSquares(), 0.001);
}

TEST (ShapeTest, QuickSortFunction)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   sort->quickSort(areaAscendingComparison);

   ASSERT_NEAR(0.75, (*shapes)[0]->area(), 0.001);
   ASSERT_NEAR(0.25*3.1415, (*shapes)[1]->area(), 0.001);
   ASSERT_NEAR(3.1415, (*shapes)[2]->area(), 0.001);
   ASSERT_NEAR(30, (*shapes)[3]->area(), 0.001);
}

TEST (ShapeTest, QuickSortOperator)
{
  std::vector<Shape*>* shapes = new std::vector<Shape*>
   {
       new Circle(1.0),
       new Circle(0.5),
       new Rectangle(5.0, 6.0),
       new Rectangle(0.5, 1.5)
   };

   Sort* sort = new Sort(shapes);
   AscendingComparison ascendingComparison("area");
   sort->quickSort(ascendingComparison);

   ASSERT_NEAR(0.75, (*shapes)[0]->area(), 0.001);
   ASSERT_NEAR(0.25*3.1415, (*shapes)[1]->area(), 0.001);
   ASSERT_NEAR(3.1415, (*shapes)[2]->area(), 0.001);
   ASSERT_NEAR(30, (*shapes)[3]->area(), 0.001);
}
