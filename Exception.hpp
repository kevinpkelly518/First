#pragma once

#include <exception>

class InvalidDateException : public std::exception {};

class NoTaskException : public std::exception {};
class ExistingTaskException : public std::exception {};
class InvalidIndexException : public std::exception {};

class NoMealException : public std::exception {};
class ExistingMealException : public std::exception {};
