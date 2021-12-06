#pragma once

#include <exception>

class InvalidDateException : public std::exception {};

class NoCardException : public std::exception {};
class ExistingCardException : public std::exception {};
class InvalidIndexException : public std::exception {};

class NoMealException : public std::exception {};
class ExistingMealException : public std::exception {};
