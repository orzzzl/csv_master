CC=g++
CFLAGS=-std=c++11

all: csv_master

csv_master:  *.h *.cpp
		$(CC) $(CFLAGS) *.cpp -o csv_master

