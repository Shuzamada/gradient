#include <iostream>
#include <vector>
#include "tdoa.h"
#include "io_utils.h"

int main()
{
  using namespace tdoa;
  
  // Points knownPoints = {
  //   Point(50.0, 75.0),   // D
  //   Point(100.0, 80.0),  // E
  //   Point(40.0, 10.0)   // F
  // };
  
  // Points realUnknownPoints = {
  //   Point(70.0, 30.0),   // A 
  //   Point(80.0, 70.0),   // B 
  //   Point(50.0, 20.0)    // C 
  // };
  // std::vector< double > knownTDOA = calculateTDOAValues(realUnknownPoints, knownPoints);
  
  std::vector< Point > knownPoints;
  std::vector< double > timeDifferences;
  
  readPoints(std::cin, knownPoints, 3);
  readTimeDifferences(std::cin, timeDifferences, 9);
  
  Points initialGuess = { //+-rand
    Point(20.0, 50.0),   // A 
    Point(100.0, 100.0), // B 
    Point(50.0, 60.0)    // C 
  };
  Points optimizedPoints = optimizeCoordinates(initialGuess, knownPoints, timeDifferences);
  printResults(std::cout, optimizedPoints);
  return 0;
}
