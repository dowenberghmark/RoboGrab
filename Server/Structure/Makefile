#
# Makefile for server and testing client.
#
#
UNAME := $(shell uname)
CC=g++
PORT=1500
SERVERIP=
ifeq ($(UNAME), Darwin)
MONGODB= -I/usr/local/Cellar/include/bsoncxx/v_noabi -I/usr/local/Cellar/include/mongocxx/v_noabi -L/usr/local/Cellar/lib -lmongocxx -lbsoncxx
else
MONGODB=
endif
LDFLAGS =

all: server server

server:
	$(CC) -std=c++11 -stdlib=libc++ *.cpp $(LDFLAGS) $(MONGODB)

clean:
	rm -f *.o
