#include <iostream>
#include <iomanip>
#include "tdoa.h"

int main()
{
  using namespace tdoa;
  std::cout << "TDOA Inverse Localization Program" << "\n";
  
  Points knownPoints = {
    Point(5.0, 5.0),   // D
    Point(10.0, 0.0),  // E
    Point(0.0, 10.0)   // F
  };
  
  Points realUnknownPoints = {
    Point(7.0, 3.0),   // A 
    Point(8.0, 7.0),   // B 
    Point(5.0, 2.0)    // C 
  };
  
  std::vector< double > knownTDOA = calculateTDOAValues(realUnknownPoints, knownPoints);
  
  std::cout << "Known TDOA values (based on real coordinates):" << "\n";
  for (size_t i = 0; i < knownTDOA.size(); ++i)
  {
    std::cout << std::fixed << std::setprecision(2) << knownTDOA[i] << " ";
    if ((i + 1) % 3 == 0) std::cout << "\n";
  }
  
  Points initialGuess = { //rand
    Point(0.0, 0.0),   // A 
    Point(10.0, 10.0), // B 
    Point(5.0, 0.0)    // C 
  };
  
  std::cout << "Starting optimization with initial guess:" << "\n";
  std::cout << "A: (" << initialGuess[0].x_ << ", " << initialGuess[0].y_ << ")" << "\n";
  std::cout << "B: (" << initialGuess[1].x_ << ", " << initialGuess[1].y_ << ")" << "\n";
  std::cout << "C: (" << initialGuess[2].x_ << ", " << initialGuess[2].y_ << ")" << "\n";
  
  Points optimizedPoints = optimizeCoordinates(initialGuess, knownPoints, knownTDOA);
  
  std::cout << "\nOptimized coordinates:" << "\n";
  std::cout << "A: (" << optimizedPoints[0].x_ << ", " << optimizedPoints[0].y_ << ")" << "\n";
  std::cout << "B: (" << optimizedPoints[1].x_ << ", " << optimizedPoints[1].y_ << ")" << "\n";
  std::cout << "C: (" << optimizedPoints[2].x_ << ", " << optimizedPoints[2].y_ << ")" << "\n";
  
  std::cout << "\nReal coordinates:" << "\n";
  std::cout << "A: (" << realUnknownPoints[0].x_ << ", " << realUnknownPoints[0].y_ << ")" << "\n";
  std::cout << "B: (" << realUnknownPoints[1].x_ << ", " << realUnknownPoints[1].y_ << ")" << "\n";
  std::cout << "C: (" << realUnknownPoints[2].x_ << ", " << realUnknownPoints[2].y_ << ")" << "\n";
  
  return 0;
}
