#ifndef CIRCLE_H
#define CIRCLE_H

#include "ishape.h"
#include "segment.h"
#include "point.h"
#include "vector.h"

namespace geometry {

class Circle : public IShape {
 public:
  Circle();
  Circle(const Point &p, const int &r);
  Circle(const Circle &s);

  Circle &Move(const Vector &v) override;
  bool ContainsPoint(const Point &p) const override;
  bool CrossesSegment(const Segment &s) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
  bool CheckPoint(const Point &p) const;

 private:
  Point p_;
  int r_;
};
}  // namespace geometry

#endif  // CIRCLE_H
