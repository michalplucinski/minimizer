CC=g++
VPATH=trunk
CFLAGS=-Wall -ansi -I$(VPATH)
LDFLAGS=-lgsl -lgslcblas

all: minimization

minimization: matrix.o point.o matrix3.o fxn.o atom.o main.cpp
		$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

fxn.o: fxn.cpp
		$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

atom.o: atom.cpp
		$(CC) $(CFLAGS) -c $< -o $@

matrix.o: matrix.cpp
		$(CC) $(CFLAGS) -c $< -o $@

point.o: point.cpp
		$(CC) $(CFLAGS) -c $< -o $@

matrix3.o: matrix3.cpp
		$(CC) $(CFLAGS) -c $< -o $@

fxn.cpp: fxn.hpp point.hpp matrix.hpp
atom.cpp: atom.hpp point.hpp
point.cpp: point.hpp matrix.hpp
matrix.cpp: matrix.hpp minexcept.hpp

clean:
		rm -rf *o minimization
