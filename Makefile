.PHONY: all

CXX = g++
CXXFLAGS = -std=c++20 -Iinclude -Werror -Wall -Wpedantic -Wextra -g

SRC = src/main.cpp
OUT = runec

all: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)
