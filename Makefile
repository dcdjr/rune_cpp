.PHONY: all clean run

CXX = g++
CXXFLAGS = -std=c++20 -Iinclude -Werror -Wall -Wpedantic -Wextra -g

SRC = src/main.cpp src/lexer.cpp src/token.cpp

OUT = runec

all: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm $(OUT)

run: all
	./$(OUT)
