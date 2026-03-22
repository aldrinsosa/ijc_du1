all: primes primes-i

primes:
	gcc primes.c eratosthenes.c error.c -DNO_CHECK -o primes -g -std=c11 -pedantic -Wall -Wextra -lm
	
primes-i: 
	gcc primes.c eratosthenes.c error.c -DUSE_INLINE -DNO_CHECK -o primes-i -g -std=c11 -pedantic -Wall -Wextra -lm

run: all
	ulimit -s 60000 && ./primes
	ulimit -s 60000 && ./primes-i