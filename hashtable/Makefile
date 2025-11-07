# Makefile for hashtable module
#
# William Bowles, November 6th, 2025. 

OBJS = hashtest.o hashtable.o ../lib/file.o hash.o ../lib/mem.o ../set/set.o
LIBS = 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib -I../set
CC = gcc
MAKE = make
# for memory test
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

hashtest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hashtest.o: hashtable.h ../lib/file.h
hashtable.o: hashtable.h hash.h ../lib/mem.h ../set/set.h
../lib/file.o: ../lib/file.h
hash.o: hash.h
../lib/mem.o: ../lib/mem.h
../set/set.o: ../set/set.h


.PHONY: test valgrind clean

test: hashtest 
	./hashtest

valgrind: hashtest
	$(VALGRIND) ./hashtest

clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f hashtest
	rm -f core
