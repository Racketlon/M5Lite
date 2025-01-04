# Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -O2
SRC = compiler.cpp src/parser.cpp src/button.cpp src/input.cpp src/label.cpp
OBJ = $(SRC:.cpp=.o)

all: compiler

compiler: $(OBJ)
	$(CXX) $(CXXFLAGS) -o compiler $(OBJ)

# Rule to compile compiler.cpp at the top level
compiler.o: compiler.cpp
	$(CXX) $(CXXFLAGS) -c compiler.cpp -o compiler.o

# Rule to compile src/parser.cpp
src/parser.o: src/parser.cpp
	$(CXX) $(CXXFLAGS) -c src/parser.cpp -o src/parser.o

# Generic rule for other src/*.cpp files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o src/*.o compiler
