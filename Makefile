CC=g++
VPATH=trunk
CFLAGS=-Wall -ansi -I$(VPATH)
LDFLAGS=-lgsl -lgslcblas

all: minimization

minimization: point.o fxn.o atom.o main.cpp
		$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

fxn.o: fxn.cpp
		$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

atom.o: atom.cpp
		$(CC) $(CFLAGS) -c $< -o $@

point.o: point.cpp
		$(CC) $(CFLAGS) -c $< -o $@

fxn.cpp: fxn.hpp point.hpp
atom.cpp: atom.hpp point.hpp
point.cpp: point.hpp

clean:
		rm -rf *o minimization
