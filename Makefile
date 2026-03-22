CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra

all: primes primes-i no-comment

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

primes.o: primes.c bitarray.h
	$(CC) $(CFLAGS) -c primes.c -o primes.o -DNO_CHECK

primes-i.o: primes.c bitarray.h
	$(CC) $(CFLAGS) -c primes.c -o primes-i.o -DNO_CHECK -DUSE_INLINE

eratosthenes.o: eratosthenes.c bitarray.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

eratosthenes-i.o: eratosthenes.c bitarray.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes-i.o -DUSE_INLINE

no-comment.o: no-comment.c
	$(CC) $(CFLAGS) -c no-comment.c -o no-comment.o

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) primes.o eratosthenes.o error.o -o primes -lm

primes-i: primes-i.o eratosthenes-i.o error.o
	$(CC) $(CFLAGS) primes-i.o eratosthenes-i.o error.o -o primes-i -lm

no-comment: no-comment.o error.o
	$(CC) $(CFLAGS) no-comment.o error.o -o no-comment

run: all
	ulimit -s 60000 && ./primes
	ulimit -s 60000 && ./primes-i
	./no-comment no-comment.c
	./no-comment no-comment.c >no-comment-result