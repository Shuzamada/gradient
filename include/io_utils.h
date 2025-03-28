#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <iostream>
#include <vector>
#include "tdoa.h"

namespace tdoa
{
  class IOStreamGuard
  {
  public:
    IOStreamGuard(std::basic_ios< char >& s);
    ~IOStreamGuard();
  private:
    std::basic_ios< char >& s_;
    std::streamsize width_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream& readPoints(std::istream& in, std::vector< Point >& points, int numPoints);
  std::istream& readTimeDifferences(std::istream& in, std::vector< double >& differences, int numDifferences);
  std::ostream& printResults(std::ostream& out, const Points& optimizedPoints);
}

#endif // IO_UTILS_H
