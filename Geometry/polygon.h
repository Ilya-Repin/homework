#ifndef POLYGON_H
#define POLYGON_H

#include "ishape.h"
#include <vector>
#include "segment.h"
#include "ray.h"
#include "point.h"

namespace geometry {

class Polygon : public IShape {
 public:
  Polygon();
  explicit Polygon(const std::vector<Point> &points);
  Polygon(const Polygon &p);

  Polygon &Move(const Vector &v) override;
  bool ContainsPoint(const Point &p) const override;
  bool CrossesSegment(const Segment &s) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;

 private:
  std::vector<Point> points_;
};
}  // namespace geometry

#endif  // POLYGON_H
