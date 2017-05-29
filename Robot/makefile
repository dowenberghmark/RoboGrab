all: controller chat

controller: controller.o protocol.o
	gcc -o controller controller.o protocol.o

chat: chat.o protocol.o
	gcc -o chat chat.o protocol.o

controller.o: controller.c
	gcc -c controller.c

protocol.o: protocol.c
	gcc -c protocol.c

chat.o: chat.c
	gcc -c chat.c

clean:
	rm -rf *o controller chat
