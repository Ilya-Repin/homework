#ifndef VECTOR_H
#define VECTOR_H

#include <string>
namespace geometry {

class Vector {
 public:
  explicit Vector(int x = 0, int y = 0);
  Vector(const Vector &other);

  int GetX() const;
  int GetY() const;

  Vector &operator+=(const Vector &other);
  Vector &operator-=(const Vector &other);
  Vector &operator/=(const int &num);
  Vector &operator*=(const int &num);
  std::string ToString() const;

 private:
  int x_ = 0;
  int y_ = 0;
};

Vector operator-(const Vector &other);
Vector operator+(const Vector &other);

Vector operator+(const Vector &first, const Vector &second);
Vector operator-(const Vector &first, const Vector &second);
Vector operator*(const Vector &v, const int &num);
Vector operator/(const Vector &v, const int &num);

bool operator==(const Vector &first, const Vector &second);
bool operator!=(const Vector &first, const Vector &second);

double VectorProduct(const Vector &first, const Vector &second);
double ScalarProduct(const Vector &first, const Vector &second);

}  // namespace geometry

#endif  // VECTOR_H
