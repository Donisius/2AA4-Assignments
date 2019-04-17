CFLAGS= -Wall -c
all: test doc

experiment: execute
	./execute
	rm execute *.o

test: tests
	./tests
	rm tests *.o

execute: main.o Grid2D.o
	g++ main.o Grid2D.o -o execute

tests: testGrid2D.o Grid2D.o
	g++ testGrid2D.o Grid2D.o -o tests

main.o: ./experiment/main.cpp
	g++ $(CFLAGS) ./experiment/main.cpp

Grid2D.o: ./src/Grid2D.cpp
	g++ $(CFLAGS) ./src/Grid2D.cpp

testGrid2D.o: ./test/testGrid2D.cpp
	g++ $(CFLAGS) ./test/testGrid2D.cpp

doc:
	doxygen doxConfig

clean:
	rm *.o
