#
# Makefile for server and testing client.
#
#
UNAME_S := $(shell uname -s)
CC=g++-4.9
PORT=1500
SERVERIP=
ifeq ($(UNAME_S), Darwin)
MONGODB= -I/usr/local/Cellar/include/bsoncxx/v_noabi -I/usr/local/Cellar/include/mongocxx/v_noabi
MLIB = -L/usr/local/Cellar/lib -lmongocxx -lbsoncxx
LDFLAGS=-Wl,-rpath,/usr/local/Cellar/lib
OBJECTS := $(shell find . ! -name "sensor.*" -name "*.cpp" -maxdepth 1)
else
MONGODB=-I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi
MLIB = -L/usr/local/lib -lmongocxx -lbsoncxx
LDFLAGS=-Wl,-rpath,/usr/local/lib -lbluetooth
OBJECTS := $(shell find . ! -name "mac_sensor.*" -name "*.cpp" -maxdepth 1)
endif

all: server

server:
	$(CC) -Wall -std=c++11 $(OBJECTS) -o $@ $^ $(LDFLAGS) $(MONGODB) $(MLIB)

run:

	./server

clean:
	rm -f *.o
	rm server
