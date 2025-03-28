#ifndef TDOA_H
#define TDOA_H

#include <vector>
#include <cmath>

namespace tdoa
{
  struct Point 
  {
    double x_ = 0.0;
    double y_ = 0.0;
    
    Point(double x, double y):
      x_(x),
      y_(y)
      {}
  };
  using Points = std::vector<Point>;
  double calculateDistance(const Point& p1, const Point& p2);
}


#endif // TDOA_H
 
