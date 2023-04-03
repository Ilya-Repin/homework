#include "../ray.h"

namespace geometry {

Ray::Ray() : p_(), v_() {
}

Ray::Ray(const Point &a, const Point &b) : p_(a), v_(Vector(b.GetX() - a.GetX(), b.GetY() - a.GetY())) {
}

Ray::Ray(const Point &p, const Vector &v) : p_(p), v_(v) {
}

Ray::Ray(const Ray &r) : p_(r.p_), v_(r.v_) {
}

const Point &Ray::GetPoint() const {
  return p_;
}

const Vector &Ray::GetVector() const {
  return v_;
}

Ray &Ray::Move(const Vector &v) {
  p_.Move(v);
  return *this;
}

bool Ray::ContainsPoint(const Point &p) const {
  if (p_.GetX() == p.GetX() && p_.GetY() == p.GetY()) {
    return true;
  }

  Vector vec(p.GetX() - p_.GetX(), p.GetY() - p_.GetY());
  return ScalarProduct(vec, v_) >= 0 && VectorProduct(vec, v_) == 0;
}

bool Ray::CrossesSegment(const Segment &s) const {
  if (ContainsPoint(s.GetPointA()) || ContainsPoint(s.GetPointB())) {
    return true;
  }

  Line l(p_, v_);

  if (!l.CrossesSegment(s)) {
    return false;
  }

  return CheckIntersection(s, *this);
}

std::unique_ptr<IShape> Ray::Clone() const {
  return std::make_unique<Ray>(*this);
}

std::string Ray::ToString() const {
  std::string s = "Ray(" + p_.ToString() + ", " + v_.ToString() + ")";
  return s;
}

bool CheckIntersection(const Segment &s, const Ray &r) {
  Vector vec1(r.GetPoint().GetX() - s.GetPointA().GetX(), r.GetPoint().GetY() - s.GetPointA().GetY());
  Vector vec2(s.GetPointB().GetX() - s.GetPointA().GetX(), s.GetPointB().GetY() - s.GetPointA().GetY());

  return VectorProduct(vec2, vec1) * VectorProduct(vec2, r.GetVector()) <= 0;
}
}  // namespace geometry