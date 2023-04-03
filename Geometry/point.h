#ifndef POINT_H
#define POINT_H

#include "ishape.h"

namespace geometry {

class Point : public IShape {
 public:
  Point();
  Point(const int &x, const int &y);
  Point(const Point &p);

  const int &GetX() const;
  const int &GetY() const;

  Point &Move(const Vector &v) override;
  bool ContainsPoint(const Point &) const override;
  bool CrossesSegment(const Segment &) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;

 private:
  int x_;
  int y_;
};

Vector operator-(const Point &p1, const Point &p2);

}  // namespace geometry

#endif  // POINT_H
