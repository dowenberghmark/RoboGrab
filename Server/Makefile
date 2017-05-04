#
# Makefile for server and testing client.
#
#
CC=gcc
PORT=1500
DANIELIP=130.238.251.150
all: server testingclient

server: server.o
	$(CC) -o $@ $^  

testingclient: testingclient.o
	$(CC) -o $@ $^

run_server: server
	./server $(PORT)

run_client_wrong: testingclient
	./testingclient connect $(PORT) $(DANIELIP)


run_client_correct: testingclient
	./testingclient CONNECT $(PORT) $(DANIELIP)

clean:
	rm -f server testingclient *.o
