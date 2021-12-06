#pragma once

#include "Exception.hpp"

#include <memory>


namespace First {


class Month {
public:
  virtual ~Month() = default;

  static std::unique_ptr<Month> make(unsigned int year, unsigned int month);
  bool includes(unsigned int day) const;

  std::unique_ptr<Month> clone() const;

protected:
  Month(unsigned int e) : end(e) {}

  virtual Month* clone_implementation() const = 0;

  unsigned int start = 1;
  unsigned int end;
};

class January : public Month {
public:
  January() : Month(31) {}

private:
  Month* clone_implementation() const override;
};

class February : public Month {
public:
  February(unsigned int year) : Month(28) {
    if (year % 4 == 0) {
      end = 29;
    }
  }

private:
  Month* clone_implementation() const override;
};

class March : public Month {
public:
  March() : Month(31) {}

private:
  Month* clone_implementation() const override;
};

class April : public Month {
public:
  April() : Month(30) {}

private:
  Month* clone_implementation() const override;
};

class May : public Month {
public:
  May() : Month(31) {}

private:
  Month* clone_implementation() const override;
};

class June : public Month {
public:
  June() : Month(30) {}

private:
  Month* clone_implementation() const override;
};

class July : public Month {
public:
  July() : Month(31) {}

private:
  Month* clone_implementation() const override;
};

class August : public Month {
public:
  August() : Month(31) {}

private:
  Month* clone_implementation() const override;
};

class September : public Month {
public:
  September() : Month(30) {}

private:
  Month* clone_implementation() const override;
};

class October : public Month {
public:
  October() : Month(31) {}

private:
  Month* clone_implementation() const override;
};

class November : public Month {
public:
  November() : Month(30) {}

private:
  Month* clone_implementation() const override;
};

class December : public Month {
public:
  December() : Month(31) {}

private:
  Month* clone_implementation() const override;
};

struct Date {
  Date(unsigned int year, unsigned int month, unsigned int day);
  ~Date() = default;
  Date(const Date& date);
  Date(Date&& other) = default;
  Date& operator=(const Date& other);
  Date& operator=(Date&& other) = default;


  unsigned int year;
  std::unique_ptr<Month> month;
  unsigned int day;
};

int mtoi(const Month* month);

bool operator<(const Date& left, const Date& right);


} // end namespace First
