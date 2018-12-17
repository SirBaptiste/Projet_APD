CFLAGS= -Wall -g
CC=mpicc
LDLIBS=-lm

all : sequent dist

sequent : sequent.o conway.o
	$(CC) $(CFLAGS) -o $@ $^

dist : dist.o conway.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)
	
test : main.o fonctions.o
	$(CC) $(CFLAGS) -o $@ $^

clean :
	$(RM) *.o seq dist test

