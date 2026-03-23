// bitarray.h
// Řešení IJC-DU1, příklad a), 22.3.2026
// Autor: Aldrin Joseph Sosa Dominguez, FIT
// Přeloženo: clang 17.0.0
// Header file with macros and inline functions for bit array manipulation
#ifndef BITARRAY
#define BITARRAY
#include "error.h"
#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

#ifndef NO_CHECK
    #define CHECK_LIMIT(array_name, index) \
        do{\
            unsigned long _limit = bitarray_size((array_name));\
            if ((index) >= _limit) \
            {\
                error_exit("bitarray_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)(index), (unsigned long)(_limit - 1));\
            }\
        } while (0)
    //the 0 next to error_exit is for the code in order to compile
    //if the limit is exceed the program finishes with error else returns 0
    #define CHECK_LIMIT_EXPR(array_name, index)\
        (((index) >= (bitarray_size((array_name)))) ? (error_exit("bitarray_getbit: Index %lu mimo rozsah 0..%lu",(unsigned long)(index), (unsigned long)((bitarray_size((array_name))) - 1)), 0) : 0)
#else
    #define CHECK_LIMIT(array_name, index)
    #define CHECK_LIMIT_EXPR(array_name, index) (0)
#endif
    

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
    inline void bitarray_setbit(bitarray_t array_name, unsigned long idx, bool expression){
        CHECK_LIMIT(array_name, idx);
        //get in which block from the array the bit resides
        unsigned long idx_block = 1 + (idx / BITS_PER_BLOCK);
        //get in which bit from the block the bit is located
        unsigned long idx_bit = idx % BITS_PER_BLOCK;
        //creates a bitmask with a 1 in the place where the bit is located
        unsigned long bitmask = 1UL << idx_bit;
        if (expression)
        {
            //set the bit at 1
            array_name[idx_block] = array_name[idx_block] | bitmask;
        }
        else{
            //set the bit at 0
            array_name[idx_block] = array_name[idx_block] & ~bitmask;
        }
    }
    inline bool bitarray_getbit(bitarray_t array_name, unsigned long idx){
        CHECK_LIMIT(array_name, idx);
        unsigned long idx_block = 1 + (idx / BITS_PER_BLOCK);
        unsigned long idx_bit = idx % BITS_PER_BLOCK;
        unsigned long bitmask = 1UL << idx_bit;
        //compares the block of the array with the mask
        unsigned long result = array_name[idx_block] & bitmask;
        //if the bit was set at 1 there would be some kind of value different than 0 in result
        if(result != 0)
            return true;
        return false;
    }
#else
    #define bitarray_free(array_name) free((array_name))
    #define bitarray_size(array_name) ((array_name)[0])
    //add do while to limit the scope of the variables and the if statments
    #define bitarray_fill(array_name, expression) \
    do {\
        unsigned long _size = bitarray_size(array_name);\
        unsigned long _blocks = ((_size + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK);\
        if ((expression)){\
            for (unsigned long _i = 1; _i <= _blocks; _i++){\
                (array_name)[_i] = ~0UL;\
            }\
        }\
        else { \
            for (unsigned long _i = 1; _i <= _blocks; _i++){\
                (array_name)[_i] = 0;\
            }\
        }\
    } while(0)
    #define bitarray_setbit(array_name, idx, expression) \
        do{\
            CHECK_LIMIT(array_name, idx);\
            unsigned long _idx_block = 1 + ((idx) / BITS_PER_BLOCK);\
            unsigned long _idx_bit = (idx) % BITS_PER_BLOCK;\
            unsigned long _bitmask = 1UL << _idx_bit;\
            if ((expression))\
            {\
                (array_name)[_idx_block] = (array_name)[_idx_block] | _bitmask;\
            }\
            else{\
                (array_name)[_idx_block] = (array_name)[_idx_block] & ~_bitmask;\
            }\
        } while(0)

    //if the limit isn't exceed gets a 0 that is ignorred due to the coma operator    
    //replace all the variables from the inline function with the calculations
    #define bitarray_getbit(array_name, idx) \
        ((void)CHECK_LIMIT_EXPR(array_name, idx),(((array_name)[1 + ((idx) / BITS_PER_BLOCK)] & (1UL << ((idx) % BITS_PER_BLOCK))) != 0))


#endif
#endif
