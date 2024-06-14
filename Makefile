#
#

TARGET=./bin
CC = g++ -std=c++17

all: sniffer

sniffer: sniffer.o
	$(CC) -o sniffer sniffer.o 

sniffer.o: sniffer.cpp
	$(CC) -c sniffer.cpp -o sniffer.o 
#link

clean:
	rm sniffer.o sniffer