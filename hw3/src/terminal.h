#ifndef TERMINAL_H
#define TERMINAL_H

#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/circular_sector.h"
#include "../src/rectangle.h"
#include "../src/ellipse.h"
#include "../src/triangle.h"
#include "../src/sort.h"
#include <regex>
#include <vector>
#include <string>

using namespace std;

class Terminal
{
public:
    // you can use regular expression to get useful token from "Input string"
    Terminal(std::string in): _in(in)
    {
      // Input string like this => "Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc"
        //....

    }

    std::string showResult()
    {
      //  ..... // return result For example: [XXX, XXX, XXX]
      std::vector<Shape*>* shapes = new std::vector<Shape*>{};

      string shapeTemp;           // all shape
      string ellipseTemp;         // all ellipse
      string triangleTemp;        // all triangle
      string circularSectorTemp;  // all circular_sector
      string variable;

      double NumArray[100];

      smatch result;
      regex shapeType("(Ellipse \\s*\\S*\\s*\\( *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *\\) ?)|(Triangle \\s*\\S*\\s*\\( *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *\\) ?)|(CircularSector \\s*\\S*\\s*\\( *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *\\) ?)");

      while(regex_search(_in, result, shapeType)){
          for (int x = 1; x < result.size(); x++) {
              shapeTemp = result.str(x);
              smatch shape;
              regex ellipseType("(Ellipse \\s*\\S*\\s*\\( *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *\\) ?)");
              regex triangleType("(Triangle \\s*\\S*\\s*\\( *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *\\) ?)");
              regex circularSectorType("(CircularSector \\s*\\S*\\s*\\( *-?\\d+\\.?\\d* *, *-?\\d+\\.?\\d* *\\) ?)");
              if(regex_search(shapeTemp, shape, ellipseType)) {
                int count = 0;
                variable = shape.str();
                smatch ellipseVariable;
                regex ellipseNum("-?\\d+\\.?\\d*");
                while(regex_search(variable, ellipseVariable, ellipseNum)) {
                  NumArray[count] = stod(ellipseVariable.str());
                  variable = ellipseVariable.suffix();
                  count++;
                }
                shapes->insert(shapes->end(), new Ellipse(NumArray[0], NumArray[1]));
              }
              else if(regex_search(shapeTemp, shape, triangleType)) {
                int count = 0;
                variable = shape.str();
                smatch triangleVariable;
                regex triangleNum("-?\\d+\\.?\\d*");
                while(regex_search(variable, triangleVariable, triangleNum)) {
                  NumArray[count] = stod(triangleVariable.str());
                  variable = triangleVariable.suffix();
                  count++;
                }
                shapes->insert(shapes->end(), new Triangle(NumArray[0], NumArray[1], NumArray[2], NumArray[3], NumArray[4], NumArray[5]));
              }
              else if(regex_search(shapeTemp, shape, circularSectorType)) {
                int count = 0;
                variable = shape.str();
                smatch circularSectorVariable;
                regex circularSectorNum("-?\\d+\\.?\\d*");
                while(regex_search(variable, circularSectorVariable, circularSectorNum)) {
                  NumArray[count] = stod(circularSectorVariable.str());
                  variable = circularSectorVariable.suffix();
                  count++;
                }
                shapes->insert(shapes->end(), new CircularSector(NumArray[0], NumArray[1]));
              }
            }
          _in = result.suffix();
        }

      Sort* sort = new Sort(shapes);

      smatch calculateWhat;
      regex callCalculate("(area )|(perimeter )|(sumOfSquares )");

      smatch incOrDec;
      regex judecIncOrDec("(inc)|(dec)");

      smatch useful;
      regex judgeUseful("((area )|(perimeter )|(sumOfSquares ))((inc)|(dec))");

      string ans = "[";

      if(regex_search(_in, useful, judgeUseful)) {
        if(regex_search(_in, calculateWhat, callCalculate)) {
          if(calculateWhat[0] == "area ") {
            if(regex_search(_in, incOrDec, judecIncOrDec)) {
              if(incOrDec[0] == "inc") {
                AscendingComparison ascendingComparison("area");
                sort->sortArea(ascendingComparison);
                ans += to_string((*shapes)[0]->area());
                if(shapes->size() != 1)
                  for(int i = 1; i < shapes->size(); i++) {
                    ans += ", " + to_string((*shapes)[i]->area());
                  }
              }
              else if(incOrDec[0] == "dec") {
                DescendingComparison descendingComparison("area");
                sort->sortArea(descendingComparison);
                ans += to_string((*shapes)[0]->area());
                if(shapes->size() != 1)
                  for(int i = 1; i < shapes->size(); i++) {
                    ans += ", " + to_string((*shapes)[i]->area());
                  }
              }
            }
          }
          else if(calculateWhat[0] == "perimeter ") {
            if(regex_search(_in, incOrDec, judecIncOrDec)) {
              if(incOrDec[0] == "inc") {
                AscendingComparison ascendingComparison("perimeter");
                sort->sortPerimeter(ascendingComparison);
                ans += to_string((*shapes)[0]->perimeter());
                if(shapes->size() != 1)
                  for(int i = 1; i < shapes->size(); i++) {
                    ans += ", " + to_string((*shapes)[i]->perimeter());
                  }
              }
              else if(incOrDec[0] == "dec") {
                DescendingComparison descendingComparison("perimeter");
                sort->sortPerimeter(descendingComparison);
                ans += to_string((*shapes)[0]->perimeter());
                if(shapes->size() != 1)
                  for(int i = 1; i < shapes->size(); i++) {
                    ans += ", " + to_string((*shapes)[i]->perimeter());
                  }
              }
            }
          }
          else if(calculateWhat[0] == "sumOfSquares ") {
            if(regex_search(_in, incOrDec, judecIncOrDec)) {
              if(incOrDec[0] == "inc") {
                AscendingComparison ascendingComparison("sumOfSquares");
                sort->sortSumOfSquares(ascendingComparison);
                ans += to_string((*shapes)[0]->sumOfSquares());
                if(shapes->size() != 1)
                  for(int i = 1; i < shapes->size(); i++) {
                    ans += ", " + to_string((*shapes)[i]->sumOfSquares());
                  }
              }
              else if(incOrDec[0] == "dec") {
                DescendingComparison descendingComparison("sumOfSquares");
                sort->sortSumOfSquares(descendingComparison);
                ans += to_string((*shapes)[0]->sumOfSquares());
                if(shapes->size() != 1)
                  for(int i = 1; i < shapes->size(); i++) {
                    ans += ", " + to_string((*shapes)[i]->sumOfSquares());
                  }
              }
            }
          }
        }
      }
      else{throw std::string("Unuseful User Input!");}

      return ans + "]";
    }

  private:
    std::string _in;
};
#endif
