all: controller chat

controller: controller.o protocol.o
	gcc -Wall -o controller controller.o protocol.o

chat: chat.o protocol.o
	gcc -Wall -o chat chat.o protocol.o

controller.o: controller.c
	gcc -std=c99 -c controller.c

protocol.o: protocol.c
	gcc -std=c99 -c protocol.c

chat.o: chat.c
	gcc -std=c99 -c chat.c

clean:
	rm -rf *o controller chat
