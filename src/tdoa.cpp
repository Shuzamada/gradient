#include "tdoa.h"
#include <cmath>

namespace tdoa
{
  double calculateDistance(const Point& p1, const Point& p2)
  {
    return std::sqrt(std::pow(p2.x_ - p1.x_, 2) + std::pow(p2.y_ - p1.y_, 2));
  }
}
 
