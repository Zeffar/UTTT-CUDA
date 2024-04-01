CXX=g++
CXXFLAGS=-std=c++23
CXXFLAGS+=-I./GUI/imgui -I./GUI/imgui/backends ./GUI/imgui/imgui.cpp ./GUI/imgui/imgui_draw.cpp ./GUI/imgui/imgui_widgets.cpp ./GUI/imgui/imgui_tables.cpp ./GUI/imgui/backends/imgui_impl_glfw.cpp ./GUI/imgui/backends/imgui_impl_opengl3.cpp ./GUI/imgui/imgui_demo.cpp

all: build run

test: test.cpp
	$(CXX) $(CXXFLAGS) test.cpp -o test -lglfw -lGL -ldl -lpthread 
	./test

build: TicTacToe.cpp
	$(CXX) $(CXXFLAGS) TicTacToe.cpp -o UTTT -lglfw -lGL -ldl -lpthread 
	./UTTT

clean:
	rm -f UTTT

run: 
	./UTTT 
