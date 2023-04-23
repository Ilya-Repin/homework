#ifndef SEGMENT_H
#define SEGMENT_H

#include "ishape.h"
#include "vector.h"
#include "line.h"
#include "point.h"

namespace geometry {

class Segment : public IShape {
 public:
  Segment();
  Segment(const Point &a, const Point &b);
  Segment(const Segment &s);

  const Point &GetPointA() const;
  const Point &GetPointB() const;

  Segment &Move(const Vector &v) override;
  bool ContainsPoint(const Point &p) const override;
  bool CrossesSegment(const Segment &s) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;

 private:
  Point a_;
  Point b_;
};

bool CheckIntersection(const Segment &x, const Segment &y);

}  // namespace geometry

#endif  // SEGMENT_H
