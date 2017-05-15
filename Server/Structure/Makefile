#
# Makefile for server and testing client.
#
#
UNAME := $(shell uname)
CC=g++
PORT=1500
SERVERIP=
ifeq ($(UNAME), Darwin)
MONGODB= -I/usr/local/Cellar/include/bsoncxx/v_noabi -I/usr/local/Cellar/include/mongocxx/v_noabi 
MLIB = -L/usr/local/Cellar/lib -lmongocxx -lbsoncxx
else
MONGODB=
endif
LDFLAGS=-Wl,-rpath,/usr/local/Cellar/lib

all: server

server:
	$(CC) -Wall -std=c++11 *.cpp -o $@ $^ $(LDFLAGS) $(MONGODB) $(MLIB) 

run:
	./server

clean:
	rm -f *.o
