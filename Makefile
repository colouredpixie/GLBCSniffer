#
#

TARGET=./bin
CC = g++ -std=c++17

all: sniffer

sniffer: sniffer.o
	$(CC) -o sniffer sniffer.o 

sniffer.o: sniffer.cpp socket.h print.h
	$(CC) -c sniffer.cpp -o sniffer.o 

clean:
	rm sniffer.o sniffer