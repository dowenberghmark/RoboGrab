IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm 

_DEPS = robolib.h protocol.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = robolib.o controller.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -std=c99 -o $@ $< $(CFLAGS)

robolib: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LDIR)/libev3dev-c.a  $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  
