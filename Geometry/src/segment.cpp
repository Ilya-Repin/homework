#include "../segment.h"

namespace geometry {

Segment::Segment() : a_(), b_() {
}

Segment::Segment(const Point &a, const Point &b) : a_(a), b_(b) {
}

Segment::Segment(const Segment &s) : a_(s.a_), b_(s.b_) {
}

const Point &Segment::GetPointA() const {
  return a_;
}

const Point &Segment::GetPointB() const {
  return b_;
}

Segment &Segment::Move(const Vector &v) {
  a_.Move(v);
  b_.Move(v);
  return *this;
}

bool Segment::ContainsPoint(const Point &p) const {
  return p.CrossesSegment(*this);
}

bool Segment::CrossesSegment(const Segment &s) const {
  if (ContainsPoint(s.GetPointA()) || ContainsPoint(s.GetPointB()) || s.ContainsPoint(a_) || s.ContainsPoint(b_)) {
    return true;
  }

  Line first(a_, b_);
  Line second(s.a_, s.b_);
  bool res = first.CrossesSegment(s) && second.CrossesSegment(*this);

  return res && CheckIntersection(*this, s);
}

std::unique_ptr<IShape> Segment::Clone() const {
  return std::make_unique<Segment>(*this);
}

std::string Segment::ToString() const {
  std::string s = ("Segment(" + a_.ToString() + ", " + b_.ToString() + ")");
  return s;
}

bool CheckIntersection(const Segment &s1, const Segment &s2) {
  int max_x1 = std::max(s1.GetPointA().GetX(), s1.GetPointB().GetX());
  int min_x2 = std::min(s2.GetPointA().GetX(), s2.GetPointB().GetX());
  int max_y1 = std::max(s1.GetPointA().GetY(), s1.GetPointB().GetY());
  int min_y2 = std::min(s2.GetPointA().GetY(), s2.GetPointB().GetY());

  return (max_x1 >= min_x2) && (max_y1 >= min_y2);
}
}  // namespace geometry