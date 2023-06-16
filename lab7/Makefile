CXX=aarch64-linux-gnu-g++
CXXFLAGS=-pthread
OBJ=Lab7_mutax
SRC=Lab7_semaphore.cpp

all:build
	scp ./$(OBJ) nvidia@192.168.55.1:~/
	ssh nvidia@192.168.55.1 '~/Lab7_mutax 5' 
build:
	$(CXX) -o $(OBJ) $(SRC) $(CXXFLAGS)
    
clean:
	rm -f $(EXE)
	rm -f $(OBJ)
