# all: ex clean

ex: main.o circularBuffer.cpp
	g++ main.o circularBuffer.cpp -o exc

main.o: main.cpp
	g++ -c main.cpp

circularBuffer.o: circularBuffer.cpp
	g++ -c circularBuffer.cpp

# clean:
# 	rm circularBuffer.o
# 	rm main.o