// primes.c
// Řešení IJC-DU1, příklad a), 22.3.2026
// Autor: Aldrin Joseph Sosa Dominguez, FIT
// Přeloženo: clang 17.0.0
// Implementation to get the last 10 prime numbers

#include "eratosthenes.h"
#include "bitarray.h"
#include <stdio.h>

int main (void) {
    bitarray_alloc(array, 444000000);
    Eratosthenes(array);
    unsigned long primes [10] = {};
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
    bitarray_free(array);
    for (int i = 10; i > 0; i--)
    {
        printf("%lu\n", primes[i - 1]);
    }
    return 0;
}

