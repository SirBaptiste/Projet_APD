CFLAGS= -Wall -g
CC=mpicc
	
test : main.o fonctions.o
	$(CC) $(CFLAGS) -o $@ $^

clean :
	$(RM) *.o test

