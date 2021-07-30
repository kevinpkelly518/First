.PHONY: all test

main: Board.cpp main.cpp
	c++ -std=c++11 $? -o $@

test: BoardTest.cpp Board.cpp
	c++ -std=c++11 $? -o $@