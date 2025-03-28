#include "tdoa.h"
#include <cmath>

namespace tdoa
{
  double calculateDistance(const Point& p1, const Point& p2)
  {
    return std::sqrt(std::pow(p2.x_ - p1.x_, 2) + std::pow(p2.y_ - p1.y_, 2));
  }

  std::vector< double > calculateTDOAValues(const Points& unknownPoints, const Points& knownPoints)
  {
    std::vector< double > tdoaValues;
    
    for (const auto& known : knownPoints)
    {
      
      tdoaValues.push_back(calculateDistance(unknownPoints[0], known) - calculateDistance(unknownPoints[1], known)); // AD - BD 
      tdoaValues.push_back(calculateDistance(unknownPoints[0], known) - calculateDistance(unknownPoints[2], known)); // AD - CD 
      tdoaValues.push_back(calculateDistance(unknownPoints[1], known) - calculateDistance(unknownPoints[2], known)); // BD - CD
    }
    
    return tdoaValues;
  }
  
  double calculateError(const std::vector< double >& knownTDOA, const std::vector< double >& calculatedTDOA)
  {
    double error = 0.0;
    for (size_t i = 0; i < knownTDOA.size(); ++i)
    {
      error += std::pow(knownTDOA[i] - calculatedTDOA[i], 2);
    }
    return error;
  }


  double calculatePartialDerivativeX(const Points& unknownPoints, 
                                    const Points& knownPoints,
                                    const std::vector< double >& knownTDOA,
                                    int pointIndex)
  {
    double h = 0.0001;
    Points pointsPlusH = unknownPoints;
    pointsPlusH[pointIndex].x_ += h;
    std::vector< double > tdoaPlusH = calculateTDOAValues(pointsPlusH, knownPoints);
    double errorPlusH = calculateError(knownTDOA, tdoaPlusH);
    std::vector< double > tdoaOriginal = calculateTDOAValues(unknownPoints, knownPoints);
    double errorOriginal = calculateError(knownTDOA, tdoaOriginal);
    return (errorPlusH - errorOriginal) / h;
  }
  
  double calculatePartialDerivativeY(const Points& unknownPoints, 
                                      const Points& knownPoints,
                                      const std::vector< double >& knownTDOA,
                                      int pointIndex)
  {
    double h = 0.0001;
    
    Points pointsPlusH = unknownPoints;
    pointsPlusH[pointIndex].y_ += h;
    
    std::vector< double > tdoaPlusH = calculateTDOAValues(pointsPlusH, knownPoints);
    double errorPlusH = calculateError(knownTDOA, tdoaPlusH);
    
    std::vector< double > tdoaOriginal = calculateTDOAValues(unknownPoints, knownPoints);
    double errorOriginal = calculateError(knownTDOA, tdoaOriginal);
    
    return (errorPlusH - errorOriginal) / h;
  }
}
 
