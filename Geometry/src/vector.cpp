#include "../vector.h"
#include <cmath>

namespace geometry {

Vector::Vector(int x, int y) : x_(x), y_(y) {
}

Vector::Vector(const Vector &other) : x_(other.x_), y_(other.y_) {
}

int Vector::GetX() const {
  return x_;
}

int Vector::GetY() const {
  return y_;
}

Vector &Vector::operator+=(const Vector &other) {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

Vector &Vector::operator-=(const Vector &other) {
  x_ -= other.x_;
  y_ -= other.y_;
  return *this;
}

Vector &Vector::operator*=(const int &num) {
  x_ *= num;
  y_ *= num;
  return *this;
}

Vector &Vector::operator/=(const int &num) {
  x_ /= num;
  y_ /= num;
  return *this;
}

Vector operator-(const Vector &other) {
  Vector v(-other.GetX(), -other.GetY());
  return v;
}

Vector operator+(const Vector &other) {
  return other;
}

Vector operator+(const Vector &first, const Vector &second) {
  Vector vec(first);
  return vec += second;
}

Vector operator-(const Vector &first, const Vector &second) {
  Vector vec(first);
  return vec -= second;
}

Vector operator*(const Vector &v, const int &num) {
  Vector vec(v);
  return vec *= num;
}

Vector operator/(const Vector &v, const int &num) {
  Vector vec(v);
  return vec /= num;
}

bool operator==(const Vector &first, const Vector &second) {
  return (first.GetX() == second.GetX() && first.GetY() == second.GetY());
}

bool operator!=(const Vector &first, const Vector &second) {
  return !(first == second);
}

std::string Vector::ToString() const {
  std::string x = "Vector(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
  return x;
}

double VectorProduct(const Vector &first, const Vector &second) {
  return first.GetX() * second.GetY() - first.GetY() * second.GetX();
}

double ScalarProduct(const Vector &first, const Vector &second) {
  return first.GetX() * second.GetX() + first.GetY() * second.GetY();
}
}  // namespace geometry