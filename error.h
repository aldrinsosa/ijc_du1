// error.h
// Řešení IJC-DU1, příklad b), 22.3.2026
// Autor: Aldrin Joseph Sosa Dominguez, FIT
// Přeloženo: clang 17.0.0
// Header file for error 

#ifndef ERROR_H
#define ERROR_H

void warning(const char *fmt, ...);

void error_exit(const char *fmt, ...);

#endif
