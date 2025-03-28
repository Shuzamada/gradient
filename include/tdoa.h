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
    
    Point(double x = 0.0, double y = 0.0):
      x_(x),
      y_(y)
      {}
  };
  
  using Points = std::vector< Point >;
  

  double calculateDistance(const Point& p1, const Point& p2);

  void calculateTDOAValues(const Points& unknownPoints, 
                          const Points& knownPoints,
                          std::vector<double>& output);
                                           
  double calculateError(const std::vector<double>& knownTDOA, 
                       const std::vector<double>& calculatedTDOA);

  void calculatePartialDerivatives(const Points& unknownPoints, 
                                  const Points& knownPoints,
                                  const std::vector<double>& knownTDOA,
                                  Points& gradsPoint,
                                  std::vector<double>& tdoaBuffer);

  Points optimizeCoordinates(const Points& initialGuess, 
                            const Points& knownPoints,
                            const std::vector<double>& knownTDOA,
                            double learningRate = 0.01,
                            int maxIterations = 1000000,
                            double errorThreshold = 1e-4);
}

#endif // TDOA_H
