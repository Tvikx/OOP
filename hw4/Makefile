all: ex clean

ex: main.o calendar.o
	g++ main.o calendar.o -o ex

main.o: main.cpp
	g++ -c main.cpp

calendar.o: calendar.cpp
	g++ -c calendar.cpp

clean:
	rm calendar.o
	rm main.o