#pragma once

#include <exception>

class NoCardException : public std::exception {};
class ExistingCardException : public std::exception {};
class InvalidIndexException : public std::exception {};
