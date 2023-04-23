#ifndef LINE_H
#define LINE_H

#include "ishape.h"
#include "vector.h"
#include "point.h"
#include "segment.h"

namespace geometry {

class Line : public IShape {
 public:
  Line();
  Line(const Point &a, const Point &b);
  Line(const int &a, const int &b, const int &c);
  Line(const Point &a, const Vector &v);
  Line(const Line &l);

  Line &Move(const Vector &v) override;
  bool ContainsPoint(const Point &p) const override;
  bool CrossesSegment(const Segment &s) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;

 private:
  int a_, b_, c_;
};
}  // namespace geometry

#endif  // LINE_H
