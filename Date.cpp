#include "Date.hpp"

#include <sstream>


namespace First {


std::unique_ptr<Month> Month::make(unsigned int year, unsigned int month) {
  switch (month) {
    case 1:
      return std::make_unique<January>();
    case 2:
      return std::make_unique<February>(year);
    case 3:
      return std::make_unique<March>();
    case 4:
      return std::make_unique<April>();
    case 5:
      return std::make_unique<May>();
    case 6:
      return std::make_unique<June>();
    case 7:
      return std::make_unique<July>();
    case 8:
      return std::make_unique<August>();
    case 9:
      return std::make_unique<September>();
    case 10:
      return std::make_unique<October>();
    case 11:
      return std::make_unique<November>();
    case 12:
      return std::make_unique<December>();
    default:
      throw InvalidDateException();
  }
}

bool Month::includes(unsigned int day) const {
  return day >= start && day <= end;
}

std::unique_ptr<Month> Month::clone() const {
  return std::unique_ptr<Month>(clone_implementation());
}

Month* January::clone_implementation() const {
  return new January(*this);
}

Month* February::clone_implementation() const {
  return new February(*this);
}

Month* March::clone_implementation() const {
  return new March(*this);
}

Month* April::clone_implementation() const {
  return new April(*this);
}

Month* May::clone_implementation() const {
  return new May(*this);
}

Month* June::clone_implementation() const {
  return new June(*this);
}

Month* July::clone_implementation() const {
  return new July(*this);
}

Month* August::clone_implementation() const {
  return new August(*this);
}

Month* September::clone_implementation() const {
  return new September(*this);
}

Month* October::clone_implementation() const {
  return new October(*this);
}

Month* November::clone_implementation() const {
  return new November(*this);
}

Month* December::clone_implementation() const {
  return new December(*this);
}

Date::Date(unsigned int y, unsigned int m, unsigned int d) : year(y), month(Month::make(y, m)), day(d) {
  if (!month->includes(day)) {
    throw InvalidDateException();
  }
}

Date::Date(const Date& other) : year(other.year), month(other.month->clone()), day(other.day) {}

Date& Date::operator=(const Date& other) {
  year = other.year;
  month = other.month->clone();
  day = other.day;

  return *this;
}

std::string Date::to_string() const {
  std::ostringstream oss;
  oss << year << " " << mtoi(month.get()) << " " << day;

  return oss.str();
}

int mtoi(const Month* month) {
  if (dynamic_cast<const January*>(month)) {
    return 1;
  } else if (dynamic_cast<const February*>(month)) {
    return 2;
  } else if (dynamic_cast<const March*>(month)) {
    return 3;
  } else if (dynamic_cast<const April*>(month)) {
    return 4;
  } else if (dynamic_cast<const May*>(month)) {
    return 5;
  } else if (dynamic_cast<const June*>(month)) {
    return 6;
  } else if (dynamic_cast<const July*>(month)) {
    return 7;
  } else if (dynamic_cast<const August*>(month)) {
    return 8;
  } else if (dynamic_cast<const September*>(month)) {
    return 9;
  } else if (dynamic_cast<const October*>(month)) {
    return 10;
  } else if (dynamic_cast<const November*>(month)) {
    return 11;
  } else if (dynamic_cast<const December*>(month)) {
    return 12;
  } else {
    throw InvalidDateException();
  }
}

bool operator<(const Date& left, const Date& right) {
  if (left.year < right.year) {
    return true;
  } else if (left.year > right.year) {
    return false;
  }

  if (mtoi(left.month.get()) < mtoi(right.month.get())) {
    return true;
  } else if (mtoi(left.month.get()) > mtoi(right.month.get())) {
    return false;
  }

  return left.day < right.day;
}


} // end namespace First