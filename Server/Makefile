#
# Makefile for server and testing client.
#
#
CC=g++
FLAG=-std=c++11
PORT=5000
SERVERIP="130.238.152.70"
BFLAG=-lbluetooth
all: server testingclient sensor map

server: server.o
	$(CC) -o $@ $^  $(FLAG)

testingclient: testingclient.o
	$(CC) -o $@ $^ $(FLAG)

testingclient.o: 
	$(CC) -c -o $@ testingclient.cpp $(FLAG)

sensor: sensor.o
	$(CC) -o $@ $^ $(BFLAG) $(FLAG)
sensor.o:
	$(CC) -c -o $@ sensor.cpp  $(FLAG)

run_server: server
	./server $(PORT) $(FLAG)

map: map.o
	$(CC) -o $@ $^ $(FLAG)
map.o:
	$(CC) -c -o $@ map.cpp $(FLAG)

run_client_wrong: testingclient
	./testingclient connect $(PORT) $(SERVERIP)


run_client_correct: testingclient
	./testingclient CONNECT $(PORT) $(SERVERIP)

clean:
	rm -f map  server testingclient sensor *.o

.PHONY: clean
