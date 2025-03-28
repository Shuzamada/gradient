#include "tdoa.h"
#include <cmath>
#include <iostream>
#include <iomanip>

namespace tdoa
{
  double calculateDistance(const Point& p1, const Point& p2)
  {
    return std::sqrt(std::pow(p2.x_ - p1.x_, 2) + std::pow(p2.y_ - p1.y_, 2));
  }

  void calculateTDOAValues(const Points& unknownPoints, const Points& knownPoints, std::vector< double >& output)
  {
    output.resize(knownPoints.size() * 3);
    size_t index = 0;
    
    for (const auto& known : knownPoints)
    {
      output[index++] = calculateDistance(unknownPoints[0], known) - calculateDistance(unknownPoints[1], known); // AD - BD
      output[index++] = calculateDistance(unknownPoints[0], known) - calculateDistance(unknownPoints[2], known); // AD - CD
      output[index++] = calculateDistance(unknownPoints[1], known) - calculateDistance(unknownPoints[2], known); // BD - CD
    }
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

  void calculatePartialDerivatives(const Points& unknownPoints, 
                                  const Points& knownPoints,
                                  const std::vector< double >& knownTDOA,
                                  Points& gradsPoint,
                                  std::vector< double >& tdoaBuffer)
  {
    const double h = 0.0001;
    const size_t numPoints = unknownPoints.size();
    
    calculateTDOAValues(unknownPoints, knownPoints, tdoaBuffer);
    double errorOriginal = calculateError(knownTDOA, tdoaBuffer);
    
    Points pointsPlusH = unknownPoints;
    
    for (size_t i = 0; i < numPoints; ++i)
    {
      pointsPlusH[i].x_ += h;
      calculateTDOAValues(pointsPlusH, knownPoints, tdoaBuffer);
      double errorPlusHX = calculateError(knownTDOA, tdoaBuffer);
      gradsPoint[i].x_ = (errorPlusHX - errorOriginal) / h;
      pointsPlusH[i].x_ = unknownPoints[i].x_;
      
      pointsPlusH[i].y_ += h;
      calculateTDOAValues(pointsPlusH, knownPoints, tdoaBuffer);
      double errorPlusHY = calculateError(knownTDOA, tdoaBuffer);
      gradsPoint[i].y_ = (errorPlusHY - errorOriginal) / h;
      pointsPlusH[i].y_ = unknownPoints[i].y_;
    }
  }

  Points optimizeCoordinates(const Points& initialGuess, 
                            const Points& knownPoints,
                            const std::vector< double >& knownTDOA,
                            double learningRate,
                            int maxIterations,
                            double errorThreshold)
  {
    Points currentPoints = initialGuess;
    
    std::vector<double> tdoaBuffer(knownPoints.size() * 3);
    Points gradsPoint(currentPoints.size());
    
    calculateTDOAValues(currentPoints, knownPoints, tdoaBuffer);
    double currentError = calculateError(knownTDOA, tdoaBuffer);
    
    int iteration = 0;

    while (iteration < maxIterations && currentError > errorThreshold)
    {
      calculatePartialDerivatives(currentPoints, knownPoints, knownTDOA, gradsPoint, tdoaBuffer);
      
      for (size_t i = 0; i < currentPoints.size(); ++i)
      {
        currentPoints[i].x_ -= learningRate * gradsPoint[i].x_;
        currentPoints[i].y_ -= learningRate * gradsPoint[i].y_;
      }
      calculateTDOAValues(currentPoints, knownPoints, tdoaBuffer);
      currentError = calculateError(knownTDOA, tdoaBuffer);
      
      if (iteration % 1000 == 0)
      {
        std::cout << "Iteration: " << iteration << ", Error: "  << currentError << "\n"; //отладочная информация
      }
      
      ++iteration;
    }
    
    std::cout << "Optimization completed after " << iteration << " iterations. Final error: " << currentError << "\n"; //отладочная информация
    
    return currentPoints;
  }
}
