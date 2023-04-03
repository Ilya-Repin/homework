#ifndef RAY_H
#define RAY_H

#include "ishape.h"
#include "vector.h"
#include "point.h"
#include "segment.h"

namespace geometry {

class Ray : public IShape {
 public:
  Ray();
  Ray(const Point &a, const Point &b);
  Ray(const Point &p, const Vector &v);
  Ray(const Ray &r);

  const Point &GetPoint() const;
  const Vector &GetVector() const;

  Ray &Move(const Vector &v) override;
  bool ContainsPoint(const Point &p) const override;
  bool CrossesSegment(const Segment &s) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;

 private:
  Point p_;
  Vector v_;
};

bool CheckIntersection(const Segment &s, const Ray &r);

}  // namespace geometry

#endif  // RAY_H
