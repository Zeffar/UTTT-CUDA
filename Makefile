CXX = g++
CXXFLAGS = -std=c++23

all: build run

build: TicTacToe.cpp
	$(CXX) $(CXXFLAGS) TicTacToe.cpp -o UTTT 

clean:
	rm -f UTTT

run: 
	./UTTT 
