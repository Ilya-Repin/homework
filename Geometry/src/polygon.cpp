#include "../polygon.h"

namespace geometry {

Polygon::Polygon() : points_() {
}

Polygon::Polygon(const std::vector<Point> &points) : points_(points) {
}

Polygon::Polygon(const Polygon &p) : points_(p.points_) {
}

Polygon &Polygon::Move(const Vector &v) {
  for (size_t i = 0; i < points_.size(); ++i) {
    points_[i].Move(v);
  }

  return *this;
}

bool Polygon::ContainsPoint(const Point &p) const {
  if (points_.size() == 1 && (points_[0].GetX() != p.GetX() || points_[0].GetY() != p.GetY())) {
    return false;
  }

  Ray r(p, Point(p.GetX() + rand() % 100 + 3, p.GetY() + rand() % 100 + 3));
  int counter = 0;

  for (size_t i = 0; i < points_.size(); ++i) {
    Segment s(points_[i], points_[(i < points_.size() - 1) ? i + 1 : 0]);

    if (s.ContainsPoint(r.GetPoint())) {
      return true;
    }

    if (r.CrossesSegment(s)) {
      ++counter;
    }
  }

  return counter % 2 == 1;
}

bool Polygon::CrossesSegment(const Segment &s) const {
  for (size_t i = 0; i < points_.size() - 1; ++i) {
    Segment side(points_[i], points_[i + 1]);

    if (s.CrossesSegment(side)) {
      return true;
    }
  }

  return s.CrossesSegment(Segment(points_[0], points_[points_.size() - 1]));
}

std::unique_ptr<IShape> Polygon::Clone() const {
  return std::make_unique<Polygon>(*this);
}

std::string Polygon::ToString() const {
  std::string s = "Polygon(";

  for (size_t i = 0; i < points_.size(); ++i) {
    s += points_[i].ToString() + (i != points_.size() - 1 ? ", " : ")");
  }

  return s;
}
}  // namespace geometry