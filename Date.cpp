#include "Date.hpp"


namespace First {


std::unique_ptr<Month> Month::make(unsigned int year, unsigned int month) {
  switch (month) {
    case 1:
      return std::unique_ptr<January>(new January());
    case 2:
      return std::unique_ptr<February>(new February(year));
    case 3:
      return std::unique_ptr<March>(new March());
    case 4:
      return std::unique_ptr<April>(new April());
    case 5:
      return std::unique_ptr<May>(new May());
    case 6:
      return std::unique_ptr<June>(new June());
    case 7:
      return std::unique_ptr<July>(new July());
    case 8:
      return std::unique_ptr<August>(new August());
    case 9:
      return std::unique_ptr<September>(new September());
    case 10:
      return std::unique_ptr<October>(new October());
    case 11:
      return std::unique_ptr<November>(new November());
    case 12:
      return std::unique_ptr<December>(new December());
    default:
      throw InvalidDateException();
  }
}

bool Month::includes(unsigned int day) const {
  return day >= start && day <= end;
}

Date::Date(unsigned int y, unsigned int m, unsigned int d) : year(y), month(Month::make(y, m)), day(d) {
  if (!month->includes(day)) {
    throw InvalidDateException();
  }
}

bool operator==(const Date& left, const Date& right) {
  return left.year == right.year &&
      typeid(*left.month) == typeid(*right.month) &&
      left.day == right.day;
}


} // end namespace First