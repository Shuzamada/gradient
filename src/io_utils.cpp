#include "io_utils.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include "tdoa.h"

namespace tdoa
{ 
  IOStreamGuard::IOStreamGuard(std::basic_ios< char >& s):
    s_(s),
    width_(s.width()),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}
  
  IOStreamGuard::~IOStreamGuard()
  {
    s_.width(width_);
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }  

  std::istream& readPoints(std::istream& in, std::vector< Point >& points, int numPoints)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    points.clear();
    for (int i = 0; i < numPoints; ++i)
    {
      double x, y;
      in >> x >> y;
      points.push_back(Point(x, y));
    }
    return in;
  }

  std::istream& readTimeDifferences(std::istream& in, std::vector< double >& differences, int numDifferences)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    differences.clear();
    for (int i = 0; i < numDifferences; ++i)
    {
      double diff;
      in >> diff;
      differences.push_back(diff);
    }
    return in;
  }

  std::ostream& printResults(std::ostream& out, const Points& optimizedPoints)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    IOStreamGuard fmtguard(out);
    for (size_t i = 0; i < optimizedPoints.size(); ++i)
    {
      out << static_cast< char >('A' + i) << ": (" << std::fixed << std::setprecision(2);
      out << optimizedPoints[i].x_ << ", " << optimizedPoints[i].y_ << ")\n";
    }
    return out;
  }
}