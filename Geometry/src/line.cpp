#include "../line.h"

namespace geometry {

Line::Line() : a_(), b_(), c_() {
}

Line::Line(const Point &a, const Point &b) {
  if (a.GetX() == b.GetX()) {
    a_ = 1;
    b_ = 0;
    c_ = -a.GetX();
  } else if (a.GetY() == b.GetY()) {
    a_ = 0;
    b_ = 1;
    c_ = -a.GetY();
  } else {
    Vector v(b.GetX() - a.GetX(), b.GetY() - a.GetY());
    a_ = -v.GetY();
    b_ = (v.GetX());
    c_ = -(a_ * a.GetX() + b_ * a.GetY());
  }
}

Line::Line(const Point &a, const Vector &v) {
  a_ = -v.GetY();
  b_ = v.GetX();
  c_ = -(a_ * a.GetX() + b_ * a.GetY());
}

Line::Line(const int &a, const int &b, const int &c) : a_(a), b_(b), c_(c) {
}

Line::Line(const Line &l) : a_(l.a_), b_(l.b_), c_(l.c_) {
}

Line &Line::Move(const Vector &v) {
  c_ -= a_ * v.GetX() + b_ * v.GetY();
  return *this;
}

bool Line::ContainsPoint(const Point &p) const {
  return a_ * p.GetX() + b_ * p.GetY() + c_ == 0;
}

bool Line::CrossesSegment(const Segment &s) const {
  if (ContainsPoint(s.GetPointA()) || ContainsPoint(s.GetPointB())) {
    return true;
  }

  int val_p1 = a_ * s.GetPointA().GetX() + b_ * s.GetPointA().GetY() + c_;
  int val_p2 = a_ * s.GetPointB().GetX() + b_ * s.GetPointB().GetY() + c_;

  return (val_p1 * val_p2 <= 0);
}

std::unique_ptr<IShape> Line::Clone() const {
  return std::make_unique<Line>(*this);
}

std::string Line::ToString() const {
  std::string s = "Line(" + std::to_string(a_) + ", " + std::to_string(b_) + ", " + std::to_string(c_) + ")";
  return s;
}
}  // namespace geometry