CXX = aarch64-linux-gnu-g++
CXXFLAGS = -std=c++11
OBJ = Lab2.o
EXE = main
SRC = Lab2.cpp

all: clean $(OBJ) $(EXE)
# 	./$(EXE)

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)

