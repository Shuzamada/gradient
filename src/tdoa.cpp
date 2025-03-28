#include "tdoa.h"
#include <cmath>
#include <iostream>

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


  std::vector< double > calculatePartialDerivativesX(const Points& unknownPoints, 
                                                      const Points& knownPoints,
                                                      const std::vector< double >& knownTDOA)
  {
    const double h = 0.0001;

    const size_t numPoints = unknownPoints.size();
    std::vector< double > derivatives(numPoints);
    
    std::vector< double > tdoaOriginal = calculateTDOAValues(unknownPoints, knownPoints);
    double errorOriginal = calculateError(knownTDOA, tdoaOriginal);
    for (size_t i = 0; i < numPoints; ++i)
    {
      Points pointsPlusH = unknownPoints;
      pointsPlusH[i].x_ += h;
      std::vector< double > tdoaPlusH = calculateTDOAValues(pointsPlusH, knownPoints);
      double errorPlusH = calculateError(knownTDOA, tdoaPlusH);
      derivatives[i] = (errorPlusH - errorOriginal) / h;
    }
    
    return derivatives;
  }
  
  std::vector< double > calculatePartialDerivativesY(const Points& unknownPoints, 
                                                      const Points& knownPoints,
                                                      const std::vector< double >& knownTDOA)
  {
    const double h = 0.0001;
    const size_t numPoints = unknownPoints.size();

    std::vector< double > derivatives(numPoints);
    std::vector< double > tdoaOriginal = calculateTDOAValues(unknownPoints, knownPoints);

    double errorOriginal = calculateError(knownTDOA, tdoaOriginal);
    for (size_t i = 0; i < numPoints; ++i)
    {
      Points pointsPlusH = unknownPoints;
      pointsPlusH[i].y_ += h;
      std::vector< double > tdoaPlusH = calculateTDOAValues(pointsPlusH, knownPoints);
      double errorPlusH = calculateError(knownTDOA, tdoaPlusH);
      derivatives[i] = (errorPlusH - errorOriginal) / h;
    }
    
    return derivatives;
  }


  Points optimizeCoordinates(const Points& initialGuess, 
                              const Points& knownPoints,
                              const std::vector< double >& knownTDOA,
                              double learningRate,
                              int maxIterations,
                              double errorThreshold)
  {
    Points currentPoints = initialGuess;
    std::vector< double > currentTDOA = calculateTDOAValues(currentPoints, knownPoints);
    double currentError = calculateError(knownTDOA, currentTDOA);
    
    int iteration = 0;

    while (iteration < maxIterations && currentError > errorThreshold)
    {
      std::vector< double > gradsX = calculatePartialDerivativesX(currentPoints, knownPoints, knownTDOA);
      std::vector< double > gradsY = calculatePartialDerivativesY(currentPoints, knownPoints, knownTDOA);
      
      for (size_t i = 0; i < currentPoints.size(); ++i)
      {
        currentPoints[i].x_ -= learningRate * gradsX[i];
        currentPoints[i].y_ -= learningRate * gradsY[i];
      }
      
      currentTDOA = calculateTDOAValues(currentPoints, knownPoints);
      currentError = calculateError(knownTDOA, currentTDOA);
      
      if (iteration % 100 == 0)
      {
        std::cout << "Iteration: " << iteration << ", Error: " << currentError << "\n";
      }
      
      ++iteration;
    }
    
    std::cout << "Optimization completed after " << iteration << " iterations. Final error: " << currentError << "\n";
    
    return currentPoints;
  }
}
 
