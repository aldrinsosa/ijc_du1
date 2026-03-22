// error.c
// Řešení IJC-DU1, příklad b), 22.3.2026
// Autor: Aldrin Joseph Sosa Dominguez, FIT
// Přeloženo: clang 17.0.0
// Implementation of error functions

#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warning(const char *fmt, ...){
    fprintf(stderr, "Warning: ");

    //prepares the variable for the list
    va_list args;
    //starts the list
    va_start(args, fmt);
    //send the list to vfprintf
    vfprintf(stderr, fmt, args);
    //closes the list to avoid leaks
    va_end(args);
}
void error_exit(const char *fmt, ...){
    fprintf(stderr, "Error: ");

    //prepares the variable for the list
    va_list args;
    //starts the list
    va_start(args, fmt);
    //send the list to vfprintf
    vfprintf(stderr, fmt, args);
    //closes the list to avoid leaks
    va_end(args);
    //kills the program
    exit(1);
}
