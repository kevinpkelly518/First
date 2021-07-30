.PHONY: test

test: BoardTest.cpp Board.cpp
	c++ -std=c++11 $? -o $@