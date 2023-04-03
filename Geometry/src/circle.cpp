#include "../circle.h"

namespace geometry {

Circle::Circle() : p_(), r_() {
}

Circle::Circle(const Point &p, const int &r) : p_(p), r_(r) {
}

Circle::Circle(const Circle &c) : p_(c.p_), r_(c.r_) {
}

Circle &Circle::Move(const Vector &v) {
  p_.Move(v);
  return *this;
}

bool Circle::ContainsPoint(const Point &p) const {
  return ((p.GetX() - p_.GetX()) * (p.GetX() - p_.GetX()) + (p.GetY() - p_.GetY()) * (p.GetY() - p_.GetY()) <= r_ * r_);
}

bool Circle::CrossesSegment(const Segment &s) const {
  if (CheckPoint(s.GetPointA()) && CheckPoint(s.GetPointB())) {
    return false;
  }

  double k, b;

  // Определеяем k и b прямой на которой лежит отрезок
  if (s.GetPointA().GetX() == s.GetPointB().GetX()) {
    return s.GetPointA().GetX() < p_.GetX() + r_ && s.GetPointA().GetX() > p_.GetX() - r_;
  } else {
    k = (s.GetPointA().GetY() - s.GetPointB().GetY()) / (s.GetPointA().GetX() - s.GetPointB().GetX());
  }

  b = s.GetPointA().GetY() - k * s.GetPointA().GetX();
  /*
   * Прямая: y = kx+b, Окружность (x-xc)^2 + (y-yc)^2 = r^2
   * Подставим: (x-xc)^2 - (kx+b -yc)^2 = r^2
   * Раскроем скобки: 1) x^2-2xc*x+xc^2 - (kx+b)^2 - 2yc(kx+b) + yc^2 = r^2
   *                  2) x^2-2xc*x+xc^2 - k^2 * x^2 - 2k*x*yc -2byc + yc^2 = r^2
   * Сгруппируем: (k^2+1)x^2 + (2kb-2xc-2kyc)x + (xc^2+(yc-b)^2-r^2)
   * Дискриминант: (2kb-2xc-2k*yc)^2 - 4(1+k^2)(xc^2-r^2 + b^2 -2byc +yc^2)
   * d >=0 -> отрезок пересекает или касается окружности
   */
  double d = (2 * k * b - 2 * p_.GetX() - 2 * p_.GetY() * k) *
             ((2 * k * b - 2 * p_.GetX() - 2 * p_.GetY() * k) -
              (4 + 4 * k * k) * (p_.GetX() * p_.GetX() - r_ * r_ + b * b - 2 * p_.GetY() * b + p_.GetY() * p_.GetY()));

  return d >= 0;
}

std::unique_ptr<IShape> Circle::Clone() const {
  return std::make_unique<Circle>(*this);
}

std::string Circle::ToString() const {
  std::string s = "Circle(" + p_.ToString() + ", " + std::to_string(r_) + ")";
  return s;
}

bool Circle::CheckPoint(const Point &p) const {
  return (p.GetX() - p_.GetX()) * (p.GetX() - p_.GetX()) + (p.GetY() - p_.GetY()) * (p.GetY() - p_.GetY()) < r_ * r_;
}
}  // namespace geometry