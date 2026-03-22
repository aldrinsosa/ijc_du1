// primes.c
// Řešení IJC-DU1, příklad a), 22.3.2026
// Autor: Aldrin Joseph Sosa Dominguez, FIT
// Přeloženo: clang 17.0.0
// Implementation to get the last 10 prime numbers

#include "bitarray.h"
#include <stdio.h>
#include <time.h>

#ifdef USE_INLINE
    extern inline void bitarray_free(bitarray_t array_name);
    extern inline unsigned long bitarray_size(bitarray_t array_name);
    extern inline void bitarray_fill(bitarray_t array_name, bool expression);
    extern inline void bitarray_setbit(bitarray_t array_name, unsigned long idx, bool expression);
    extern inline bool bitarray_getbit(bitarray_t array_name, unsigned long idx);
#endif

// Prototype of the Eratosthenes function
void Eratosthenes(bitarray_t pole);

int main (void) {
    clock_t start_t;
    start_t = clock();
    bitarray_create(array, 444000000);
    Eratosthenes(array);
    unsigned long primes [10];
    int counter = 0;
    for (unsigned long i = bitarray_size(array) - 1; i > 0; i--)
    {
        if (bitarray_getbit(array, i) == 0)
        {
            continue;
        }
        if (counter == 10)
        {
            break;
        }
        primes[counter] = i; 
        counter++;
    }
    for (int i = 10; i > 0; i--)
    {
        printf("%lu\n", primes[i - 1]);
    }
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start_t)/CLOCKS_PER_SEC);
    return 0;
}

