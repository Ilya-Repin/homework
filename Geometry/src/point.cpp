#include "../point.h"
#include "../segment.h"

namespace geometry {

Point::Point() : x_(0), y_(0) {
}

Point::Point(const int &x, const int &y) : x_(x), y_(y) {
}

Point::Point(const Point &p) : x_(p.x_), y_(p.y_) {
}

const int &Point::GetX() const {
  return x_;
}

const int &Point::GetY() const {
  return y_;
}

Point &Point::Move(const Vector &v) {
  x_ += v.GetX();
  y_ += v.GetY();
  return *this;
}

bool Point::ContainsPoint(const Point &other) const {
  return (x_ == other.x_ && y_ == other.y_);
}

bool Point::CrossesSegment(const Segment &other) const {
  Vector vec1(other.GetPointB().x_ - x_, other.GetPointB().y_ - y_);
  Vector vec2(x_ - other.GetPointA().x_, y_ - other.GetPointA().y_);

  return ScalarProduct(vec1, vec2) >= 0 && VectorProduct(vec1, vec2) == 0;
}

std::unique_ptr<IShape> Point::Clone() const {
  return std::make_unique<Point>(*this);
}

std::string Point::ToString() const {
  std::string s = "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
  return s;
}

Vector operator-(const Point &p1, const Point &p2) {
  return Vector(p1.GetX() - p2.GetX(), p1.GetY() - p2.GetY());
}
}  // namespace geometry