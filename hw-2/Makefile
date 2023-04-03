
CC=mpicc
CFLAGS=-I.
DEPS = hellomake.h


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: 20050111070.o hellofunc.o 
	$(CC) -o hellomake 20050111070.o hellofunc.o 
