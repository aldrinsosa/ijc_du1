all: primes primes-i

primes:
	gcc primes.c eratosthenes.c error.c -o primes -g -std=c11 -pedantic -Wall -Wextra -lm
	
primes-i: 
	gcc primes.c eratosthenes.c error.c -DUSE_INLINE -o primes-i -g -std=c11 -pedantic -Wall -Wextra -lm

run: all
	./primes
	./primes-i