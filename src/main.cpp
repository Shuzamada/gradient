#include <iostream>
#include "tdoa.h"

int main()
{
  using namespace tdoa;
  std::cout << "TDOA Inverse Localization Program" << "\n";
  
  Point pointA(1.0, 2.0);
  Point pointB(4.0, 6.0);

  double distance = calculateDistance(pointA, pointB);
  
  std::cout << "Distance between points: " << distance << "\n";
  
  return 0;
}
