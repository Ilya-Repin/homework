#ifndef ISHAPE_H
#define ISHAPE_H

#include "vector.h"
#include <memory>

namespace geometry {

class Point;
class Segment;
class Ray;
class Polygon;
class Line;
class Circle;

class IShape {
 public:
  virtual IShape &Move(const Vector &) = 0;
  virtual bool ContainsPoint(const Point &) const = 0;
  virtual bool CrossesSegment(const Segment &) const = 0;
  virtual std::unique_ptr<IShape> Clone() const = 0;
  virtual std::string ToString() const = 0;

  virtual ~IShape() = default;
};
}  // namespace geometry

#endif  // ISHAPE_H
