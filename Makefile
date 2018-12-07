CFLAGS= -Wall -g
CC=mpicc
LDLIBS=-lm

all : sequent dist

sequent : sequent.o conway.o
	$(CC) $(CFLAGS) -o $@ $^

dist : dist.o conway.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

clean :
	$(RM) *.o seq dist

