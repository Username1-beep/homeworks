#include "number.h"

number_t::number_t() = default;
number_t::~number_t() = default;
number_t::number_t(const int64_t a) : val(a) {}
number_t::number_t(const number_t &a) : val(a.val) {}

number_t::operator bool() const {
  return val != 0;
}
number_t::operator int64_t() const {
  return val;
}
number_t::operator std::string() const {
  return std::to_string(val);
}

number_t &number_t::operator=(const number_t &a) {
  val = a.val;
  return *this;
}
number_t &number_t::operator+=(const number_t &a) {
  val += a.val;
  return *this;
}
number_t &number_t::operator-=(const number_t &a) {
  val -= a.val;
  return *this;
}
number_t &number_t::operator*=(const number_t &a) {
  val *= a.val;
  return *this;
}
number_t &number_t::operator/=(const number_t &a) {
  val /= a.val;
  return *this;
}
number_t &number_t::operator%=(const number_t &a) {
  val %= a.val;
  return *this;
}
number_t &number_t::operator^=(const number_t &a) {
  val ^= a.val;
  return *this;
}
number_t &number_t::operator&=(const number_t &a) {
  val &= a.val;
  return *this;
}
number_t &number_t::operator|=(const number_t &a) {
  val |= a.val;
  return *this;
}
number_t &number_t::operator<<=(const number_t &a) {
  val <<= a.val;
  return *this;
}
number_t &number_t::operator>>=(const number_t &a) {
  val >>= a.val;
  return *this;
}

number_t &number_t::operator++() {
  ++val;
  return *this;
}
number_t &number_t::operator--() {
  --val;
  return *this;
}

number_t number_t::operator++(int) {
  return number_t(val++);
}
number_t number_t::operator--(int) {
  return number_t(val--);
}
std::ostream &operator<<(std::ostream &os, const number_t &a) {
  os << a.val;
  return os;
}
std::istream &operator>>(std::istream &is, number_t &a) {
  is >> a.val;
  return is;
}
