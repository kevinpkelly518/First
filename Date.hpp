#pragma once

#include "Exception.hpp"

#include <memory>


namespace First {


class Month {
public:
  virtual ~Month() {}

  static std::unique_ptr<Month> make(unsigned int year, unsigned int month);
  bool includes(unsigned int day) const;

protected:
  Month(unsigned int e) : end(e) {}

  unsigned int start = 1;
  unsigned int end;
};

class January : public Month {
public:
  January() : Month(31) {}
};

class February : public Month {
public:
  February(unsigned int year) : Month(28) {
    if (year % 4 == 0) {
      end = 29;
    }
  }
};

class March : public Month {
public:
  March() : Month(31) {}
};

class April : public Month {
public:
  April() : Month(30) {}
};

class May : public Month {
public:
  May() : Month(31) {}
};

class June : public Month {
public:
  June() : Month(30) {}
};

class July : public Month {
public:
  July() : Month(31) {}
};

class August : public Month {
public:
  August() : Month(31) {}
};

class September : public Month {
public:
  September() : Month(30) {}
};

class October : public Month {
public:
  October() : Month(31) {}
};

class November : public Month {
public:
  November() : Month(30) {}
};

class December : public Month {
public:
  December() : Month(31) {}
};

struct Date {
  Date(unsigned int year, unsigned int month, unsigned int day);
  Date(Date&&d) = default;

  unsigned int year;
  std::unique_ptr<Month> month;
  unsigned int day;
};

bool operator==(const Date& left, const Date& right);


} // end namespace First


namespace std {


template<>
struct hash<First::Date> {
  size_t operator()(const First::Date& date) const {
    return ((hash<unsigned int>()(date.year) ^
        (hash<unsigned int>()(date.day) << 1)) >> 1); // TODO add hash for month
  }
};


} // end namespace std
