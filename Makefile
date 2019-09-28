CC=g++
CCFLAGS=-std=c++11
CCRUN=-O3

SRC=graf.cc algorithms.cc random_graphs.cc utils.cc
OUT=graf
OBJ=graf.o

all:
	$(CC) $(CCRUN) $(CCFLAGS) $(SRC) -o $(OUT)

clean :
	rm -f *.o $(OUT)