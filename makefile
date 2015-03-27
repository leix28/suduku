ifeq ($(shell uname -s), Darwin)
CXX = clang++
else
CXX = g++
endif

all: bin/SudukuSolver.o bin/SudukuStructure.o
	$(CXX) bin/SudukuSolver.o bin/SudukuStructure.o -o bin/suduku

bin/SudukuSolver.o: src/SudukuSolver.cpp src/SudukuStructure.h
	$(CXX) -c src/SudukuSolver.cpp -o bin/SudukuSolver.o

bin/SudukuStructure.o: src/SudukuStructure.cpp src/SudukuStructure.h
	$(CXX) -c src/SudukuStructure.cpp -o bin/SudukuStructure.o

clean:
	rm -r bin/*
