all: ex clean

ex: main.o Rational.o
	g++ main.o Rational.o -o ex

main.o: main.cpp
	g++ -c main.cpp

Rational.o: Rational.cpp
	g++ -c Rational.cpp

clean:
	rm -rf *.o