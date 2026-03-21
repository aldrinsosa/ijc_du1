#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long *bitarray_t;
typedef unsigned long bitarray_index_tx;

//amount of bits per unsigned long in the current system
#define BITS_PER_BLOCK (sizeof(unsigned long) * CHAR_BIT)

//the formula calculates the amount of blocks neccesary for the bit array
//after that it's started at 0 except for the first block that contains the amount of bits in the array
#define bitarray_create(name_array,size) \
    unsigned long name_array[1 + (((size) + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK)] = {(size), 0}; \
    static_assert((size) >  0, "the bit array size must be greater than 0")

//check if the size isn't too big or too small before doing the malloc
//uses calloc to start the values at 0
//checks if calloc was succesfull
//set the first block as the size of the array
#define bitarray_alloc(name_array, size) \
    assert(((size) > 0 && (size) <= ULONG_MAX - BITS_PER_BLOCK));\
    unsigned long *name_array = (unsigned long *)calloc(1 + (((size) + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK), sizeof(unsigned long)); \
    if (name_array == NULL){ \
    fprintf(stderr, "bitarray_alloc: Chyba alokace paměti");\
    exit(1);\
    }\
    name_array[0] = (size)

#ifdef USE_INLINE
    inline void bitarray_free(bitarray_t array_name){
        free(array_name);
    }
    inline unsigned long bitarray_size (bitarray_t array_name){
        return array_name[0];
    }
    inline void bitarray_fill(bitarray_t array_name, bool expression){
        unsigned long size = bitarray_size(array_name);
        //calculates the amounts of blocks the array uses
        unsigned long blocks = ((size + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK); 
        if (expression)
        {
            for (unsigned long i = 1; i <= blocks; i++)
            {
                //makes every bit in the block 1
                array_name[i] = ~0UL;
            }
        }
        else{
            for (unsigned long i = 1; i <= blocks; i++)
            {
                array_name[i] = 0;
            }
        }
    }
#else
    #define bitarray_free(array_name) free((array_name))
    #define bitarray_size(array_name) ((array_name)[0])
    #define bitarray_fill(array_name, expression) \
    do {\
        unsigned long _size = bitarray_size(array_name);\
        unsigned long _blocks = ((_size + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK);\
        if ((expression)){\
            for (unsigned long _i = 1; i <= _blocks; i++){\
                (array_name)[i] = ~0UL;\
            }\
        }\
        else { \
            for (unsigned long _i = 1; i <= _blocks; i++){\
                (array_name)[i] = 0;\
            }\
        }\
    } while(0)


#endif