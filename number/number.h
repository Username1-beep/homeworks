#pragma once

#include <cstdint>
#include <iostream>

class number_t {
public:
  number_t();                 // пустой конструктор
  ~number_t();                // деструктор
  number_t(const int64_t);    // конструктор от числа
  number_t(const number_t &); // конструктор копирования

  explicit operator bool() const;
  operator int64_t() const;     // каст к числу
  operator std::string() const; // каст к строке

  number_t &operator=(const number_t &);  // оператор присвоения
  number_t &operator+=(const number_t &); // оператор прибавления присвоения
  number_t &operator-=(const number_t &); // оператор вычитания присвоения
  number_t &operator*=(const number_t &); // оператор умножения присвоения
  number_t &operator/=(const number_t &); // оператор деления присвоения
  number_t &operator%=(const number_t &); // оператор остатка присвоения
  number_t &operator^=(const number_t &); // оператор побитового XOR присвоения
  number_t &operator&=(const number_t &); // оператор побитового AND присвоения
  number_t &operator|=(const number_t &); // оператор побитового OR присвоения
  number_t &operator<<=(const number_t &); // оператор побитового левого сдвига присвоения
  number_t &operator>>=(const number_t &); // оператор побитового правого сдвига присвоения

  number_t &operator++();   // префиксный ++
  number_t &operator--();   // префиксный ++
  number_t operator++(int); // постфиксный --
  number_t operator--(int); // постфиксный --

  friend std::ostream &operator<<(std::ostream &,
                                  const number_t &);           // оператор вывода
  friend std::istream &operator>>(std::istream &, number_t &); // оператор ввода
private:
  int64_t val{};
};