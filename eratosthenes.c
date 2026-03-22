// erastosthenes.c
// Řešení IJC-DU1, příklad a), 22.3.2026
// Autor: Aldrin Joseph Sosa Dominguez, FIT
// Přeloženo: clang 17.0.0
// Implementation of the Eratosthenes algorithm

#include "bitarray.h"
#include <math.h>

void Eratosthenes(bitarray_t array){
    bitarray_fill(array, 1);
    bitarray_setbit(array, 0, 0);
    bitarray_setbit(array, 1, 0);
    unsigned long sqrt_size = sqrt(bitarray_size(array));
    unsigned long size = bitarray_size(array);
    for (unsigned long i = 2; i <= sqrt_size; i++)
    {
        //if it isn't 1 it isn't a prime number
        if (bitarray_getbit(array, i) != 1)
        {
            continue;
        }
        //use of unsigned long long to prevent overflow
        //we can start at i*i because al the previous number where already set 
        //usage of j += i to simulate multiplication 
        for (unsigned long long j = (unsigned long long)i*i; j < size; j += i)
        {
            bitarray_setbit(array, (unsigned long)j, 0);
        }   
    }
    
}