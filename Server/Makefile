#
# Makefile for server and testing client.
#
#
UNAME_S := $(shell uname -s)
UNAME_N := $(shell uname -n)
CC=g++
PORT=1500
SERVERIP=

ifeq ($(UNAME_N),Andys-MBP.lan)
MONGODB= -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi
MLIB = -L/usr/local/lib -lmongocxx -lbsoncxx
LDFLAGS=-Wl,-rpath,/usr/local/lib  -lcurl
OBJECTS := $(shell find . ! -name "sensor.*" -name "*.cpp" -maxdepth 1)

else ifeq ($(UNAME_S), Darwin)
MONGODB= -I/usr/local/Cellar/include/bsoncxx/v_noabi -I/usr/local/Cellar/include/mongocxx/v_noabi
MLIB = -L/usr/local/Cellar/lib -lmongocxx -lbsoncxx -I/usr/local/Cellar/boost/1.64.0_1/include  -L/usr/local/Cellar/boost/1.64.0_1/ -I/opt/local/include -I../dep/build/include -L../dep/build/lib/Release -lsioclient -lboost_system -lcurl
LDFLAGS=-Wl,-rpath,/usr/local/Cellar/lib
OBJECTS := $(shell find . ! -name "sensor.*" ! -name "job.*" ! -name "jobScheduler.*" -name "*.cpp" -maxdepth 1)

else
MONGODB=-I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/mongocxx/v_noabi
MLIB = -L/usr/local/lib -lmongocxx -lbsoncxx
LDFLAGS=-Wl,-rpath,/usr/local/lib       -lbluetooth -lm -lrt -lpthread   -lsioclient -lcurl
LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_system
OBJECTS := $(shell find . ! -name "mac_sensor.*" -name "*.cpp" -maxdepth 1)
endif

all: clean server

server: 
	$(CC) -Wall -std=c++11 $(OBJECTS) -o $@ $^ $(LIBS)  $(MONGODB) $(MLIB) $(LDFLAGS)

run:

	./server

clean:
	rm -f *.o
	rm -f server

.PHONY: clean all
