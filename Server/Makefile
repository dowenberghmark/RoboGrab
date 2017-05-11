#
# Makefile for server and testing client.
#
#
CC=g++
PORT=1500
SERVERIP=
FLAG=-std=gnu++11
BFLAG=-lbluetooth
all: server testingclient sensorconn

server: server.o
	$(CC) -o $@ $^  

testingclient: testingclient.o
	$(CC) -o $@ $^

sensorconn: sensorconn.o
	$(CC) -o $@ $^ $(BFLAG) $(FLAG)

run_server: server
	./server $(PORT)

run_client_wrong: testingclient
	./testingclient connect $(PORT) $(SERVERIP)


run_client_correct: testingclient
	./testingclient CONNECT $(PORT) $(SERVERIP)

clean:
	rm -f server testingclient sensorconn *.o
