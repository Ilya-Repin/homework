#include "rational.h"

Rational::Rational() {
  numerator_ = 0;
  denominator_ = 1;
}

Rational::Rational(int numerator, int denominator) {
  if (denominator == 0) {
    throw RationalDivisionByZero{};
  }

  numerator_ = numerator;
  denominator_ = denominator;
  Reduce();
}

Rational::Rational(const Rational &other) {
  numerator_ = other.numerator_;
  denominator_ = other.denominator_;
}

void Rational::Reduce() {
  int gcd = std::gcd(numerator_, denominator_);
  numerator_ = ((denominator_ < 0) ? -numerator_ : numerator_) / gcd;
  denominator_ = ((denominator_ < 0) ? -denominator_ : denominator_) / gcd;
}

int Rational::GetNumerator() const {
  return numerator_;
}

int Rational::GetDenominator() const {
  return denominator_;
}

void Rational::SetNumerator(int numerator) {
  numerator_ = numerator;
  Reduce();
}

void Rational::SetDenominator(int denominator) {
  if (denominator == 0) {
    throw RationalDivisionByZero{};
  }

  denominator_ = denominator;
  Reduce();
}

Rational &Rational::operator+=(const Rational &other) {
  numerator_ = numerator_ * other.denominator_ + denominator_ * other.numerator_;
  denominator_ = denominator_ * other.denominator_;
  Reduce();
  return *this;
}

Rational &Rational::operator-=(const Rational &other) {
  numerator_ = numerator_ * other.denominator_ - denominator_ * other.numerator_;
  denominator_ = denominator_ * other.denominator_;
  Reduce();
  return *this;
}

Rational &Rational::operator/=(const Rational &other) {
  if (other.numerator_ == 0) {
    throw RationalDivisionByZero{};
  }

  numerator_ = numerator_ * other.denominator_;
  denominator_ = denominator_ * other.numerator_;
  Reduce();
  return *this;
}

Rational &Rational::operator*=(const Rational &other) {
  numerator_ = numerator_ * other.numerator_;
  denominator_ = denominator_ * other.denominator_;
  Reduce();
  return *this;
}

Rational &Rational::operator++() {
  *this += 1;
  return *this;
}

Rational Rational::operator++(int) {
  Rational copy = *this;
  ++*this;
  return copy;
}

Rational &Rational::operator--() {
  *this -= 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational copy = *this;
  --*this;
  return copy;
}

std::istream &operator>>(std::istream &is, Rational &other) {
  int a;
  int b = 1;
  std::string s, as, bs;
  is >> s;
  int i = 0;

  while (s[i] != '/' && s[i] != '\0' && s[i] != ' ') {
    as.push_back(s[i]);
    ++i;
  }

  a = std::atoi(as.c_str());

  if (s[i] != '\0' && s[i] != ' ') {
    ++i;

    while (s[i] != '\0' && s[i] != ' ') {
      bs.push_back(s[i]);
      ++i;
    }

    b = std::atoi(bs.c_str());
  }

  other = Rational(a, b);
  return is;
}

std::ostream &operator<<(std::ostream &os, Rational &other) {
  if (other.GetDenominator() == 1) {
    os << other.GetNumerator();
    return os;
  }

  os << other.GetNumerator() << '/' << other.GetDenominator();
  return os;
}

std::ostream &operator<<(std::ostream &os, const Rational &other) {
  if (other.GetDenominator() == 1) {
    os << other.GetNumerator();
    return os;
  }

  os << other.GetNumerator() << '/' << other.GetDenominator();
  return os;
}

Rational operator+(const Rational &other) {
  return other;
}

Rational operator-(const Rational &other) {
  return 0 - other;
}

Rational operator+(const Rational &first, const Rational &second) {
  Rational copy = first;
  copy += second;
  return copy;
}

Rational operator-(const Rational &first, const Rational &second) {
  Rational copy = first;
  copy -= second;
  return copy;
}

Rational operator*(const Rational &first, const Rational &second) {
  Rational copy = first;
  copy *= second;
  return copy;
}

Rational operator/(const Rational &first, const Rational &second) {
  Rational copy = first;
  copy /= second;
  return copy;
}

bool operator<(const Rational &first, const Rational &second) {
  return first.GetNumerator() * second.GetDenominator() < second.GetNumerator() * first.GetDenominator();
}

bool operator>(const Rational &first, const Rational &second) {
  return second < first;
}

bool operator<=(const Rational &first, const Rational &second) {
  return !(first > second);
}

bool operator>=(const Rational &first, const Rational &second) {
  return !(first < second);
}

bool operator==(const Rational &first, const Rational &second) {
  return first.GetNumerator() * second.GetDenominator() == second.GetNumerator() * first.GetDenominator();
}

bool operator!=(const Rational &first, const Rational &second) {
  return !(first == second);
}