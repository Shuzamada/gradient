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
  using Points = std::vector< Point >;
  double calculateDistance(const Point& p1, const Point& p2);
  std::vector< double > calculateTDOAValues(const Points& unknownPoints, const Points& knownPoints);                            
  double calculateError(const std::vector<double>& knownTDOA, const std::vector<double>& calculatedTDOA);

  std::vector< double > calculatePartialDerivativesX(const Points& unknownPoints, 
                                                    const Points& knownPoints,
                                                    const std::vector< double >& knownTDOA);

  std::vector< double > calculatePartialDerivativesY(const Points& unknownPoints, 
                                                  const Points& knownPoints,
                                                  const std::vector< double >& knownTDOA);

  Points optimizeCoordinates(const Points& initialGuess, 
                              const Points& knownPoints,
                              const std::vector< double >& knownTDOA,
                              double learningRate = 0.001,
                              int maxIterations = 100000,
                              double errorThreshold = 1e-6);
}


#endif // TDOA_H
 
