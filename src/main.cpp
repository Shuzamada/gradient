#include <iostream>
#include <iomanip>
#include "tdoa.h"

int main()
{
  using namespace tdoa;
  std::cout << "TDOA Inverse Localization Program" << "\n";
  
  Points knownPoints = {
    tdoa::Point(5.0, 5.0),   // D
    tdoa::Point(10.0, 0.0),  // E
    tdoa::Point(0.0, 10.0)   // F
  };
  
  tdoa::Points unknownPoints = { //rand
    tdoa::Point(0.0, 0.0),   // A 
    tdoa::Point(10.0, 10.0), // B 
    tdoa::Point(5.0, 0.0)    // C 
  };
  
  std::vector< double > tdoaValues = tdoa::calculateTDOAValues(unknownPoints, knownPoints);

  for (size_t i = 0; i < tdoaValues.size(); ++i)
  {
    std::cout << std::fixed << std::setprecision(2) << tdoaValues[i] << " ";
    if ((i + 1) % 3 == 0) std::cout << "\n";
  }
  
  return 0;
}
