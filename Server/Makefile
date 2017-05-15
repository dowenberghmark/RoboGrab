#
# Makefile for server and testing client.
#
#
CC=g++
PORT=1500
SERVERIP=
BFLAG=-lbluetooth
all: server testingclient sensorconn map

server: server.o
	$(CC) -o $@ $^  

testingclient: testingclient.o
	$(CC) -o $@ $^

sensorconn: sensorconn.o
	$(CC) -o $@ $^ $(BFLAG)

run_server: server
	./server $(PORT)

map: map.o
	$(CC) -o $@ $^

run_client_wrong: testingclient
	./testingclient connect $(PORT) $(SERVERIP)


run_client_correct: testingclient
	./testingclient CONNECT $(PORT) $(SERVERIP)

clean:
	rm -f map  server testingclient sensorconn *.o

.PHONY: clean
