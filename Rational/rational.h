#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
#include <numeric>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 public:
  Rational();
  Rational(int numerator, int denominator = 1);  // NOLINT
  Rational(const Rational &other);

  int GetNumerator() const;
  int GetDenominator() const;
  void SetNumerator(int numerator);
  void SetDenominator(int denominator);

  Rational &operator+=(const Rational &other);
  Rational &operator-=(const Rational &other);
  Rational &operator/=(const Rational &other);
  Rational &operator*=(const Rational &other);

  Rational &operator++();
  Rational operator++(int);
  Rational &operator--();
  Rational operator--(int);

 private:
  int numerator_;
  int denominator_;

  void Reduce();
};

std::istream &operator>>(std::istream &is, Rational &other);
std::ostream &operator<<(std::ostream &os, Rational &other);
std::ostream &operator<<(std::ostream &os, const Rational &other);

Rational operator-(const Rational &other);
Rational operator+(const Rational &other);

Rational operator+(const Rational &first, const Rational &second);
Rational operator-(const Rational &first, const Rational &second);
Rational operator*(const Rational &first, const Rational &second);
Rational operator/(const Rational &first, const Rational &second);

bool operator<(const Rational &first, const Rational &second);
bool operator>(const Rational &first, const Rational &second);
bool operator<=(const Rational &first, const Rational &second);
bool operator>=(const Rational &first, const Rational &second);
bool operator==(const Rational &first, const Rational &second);
bool operator!=(const Rational &first, const Rational &second);
#endif