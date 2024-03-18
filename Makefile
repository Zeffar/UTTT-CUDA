CXX = g++
CXXFLAGS = -std=c++23

all: build

build: TicTacToe.cpp
	$(CXX) $(CXXFLAGS) TicTacToe.cpp -o UTTT

clean:
	rm -f UTTT
