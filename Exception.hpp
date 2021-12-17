#pragma once

#include <exception>

class InvalidDateException : public std::exception {};

class ExistingIdException : public std::exception {};
class NoIdException : public std::exception {};

class NoMealException : public std::exception {};
class ExistingMealException : public std::exception {};
