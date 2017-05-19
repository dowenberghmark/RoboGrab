all: controller

controller: controller.o
	gcc -o controller controller.o

controller.o: controller.c
	gcc -c controller.c

clean:
	rm -rf *o controller
