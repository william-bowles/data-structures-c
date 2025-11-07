# Makefile for counters 
#
# William Bowles. November 5th, 2025.

OBJS = counterstest.o counters.o ../lib/file.o ../lib/mem.o
LIBS = 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make
# for memory leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

counterstest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

counterstest.o: counters.h ../lib/file.h
counters.o: counters.h
../lib/file.o: ../lib/file.h

.PHONY: test valgrind clean

test: counterstest 
	./counterstest 

valgrind: counterstest 
	$(VALGRIND) ./counterstest 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f counterstest
	rm -f core

