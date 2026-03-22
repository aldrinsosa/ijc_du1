// no-comments.c
// Řešení IJC-DU1, příklad a), 22.3.2026
// Autor: Aldrin Joseph Sosa Dominguez, FIT
// Přeloženo: clang 17.0.0
// Program to delete the comments of a c file

#include "error.h"
#include <stdio.h>

typedef enum {
    NORMAL,
    STRING,
    CHAR,
    SLASH,
    ESCAPE_COMMENT,
    ESCAPE_STRING,
    ESCAPE_CHAR,
    COMMENT_LINE,
    COMMENT_BLOCK,
    COMMENT_STAR
} State;

int main (int argc, char *argv[]){
    FILE *input = stdin;

    if (argc > 1)
    {
        input = fopen(argv[1], "r");
        if (!input)
        {
            error_exit("no-comment= error at opening %s \n", argv[1]);
        }
    }
    State current_state = NORMAL;
    int ch;
    while ((ch = fgetc(input)) != EOF)
    {
        switch (current_state)
        {
        case NORMAL:
            if (ch == '\"')
            {
                putchar(ch);
                current_state = STRING;
            }
            else if (ch == '\'')
            {
                putchar(ch);
                current_state = CHAR;
            }
            else if (ch == '/')
            {
                current_state = SLASH;
            }
            else
            {
                putchar(ch);
            }
            break;
        case STRING:
            putchar(ch);
            if (ch == '\"')
            {
                current_state = NORMAL;
            }
            else if (ch == '\\')
            {
                current_state = ESCAPE_STRING;
            }
            break;
        case CHAR:
            putchar(ch);
            if (ch == '\'')
            {
                current_state = NORMAL;
            }
            else if (ch == '\\')
            {
                current_state = ESCAPE_CHAR;
            }
            break;
        case SLASH:
            if (ch == '/')
            {
                current_state = COMMENT_LINE;
            }
            else if (ch == '*')
            {
                current_state = COMMENT_BLOCK;
            }
            else if (ch == '\"')
            {
                putchar('/');
                putchar(ch);
                current_state = STRING;
            }
            else if (ch == '\'')
            {
                putchar('/');
                putchar(ch);
                current_state = CHAR;
            }
            else
            {
                putchar('/');
                putchar(ch);
                current_state = NORMAL;
            }
            break;
        case ESCAPE_COMMENT:
            current_state = COMMENT_LINE;
            break;
        case ESCAPE_STRING:
            putchar(ch);
            current_state = STRING;
            break;
        case ESCAPE_CHAR:
            putchar(ch);
            current_state = CHAR;
            break;
        case COMMENT_LINE:
            if (ch == '\\')
            {
                current_state = ESCAPE_COMMENT;
            }
            else if (ch == '\n')
            {
                putchar('\n');
                current_state = NORMAL;
            }
            break;
        case COMMENT_BLOCK:
            if (ch == '*')
            {
                current_state = COMMENT_STAR;
            }
            break;
        case COMMENT_STAR:
            if (ch == '/')
            {
                putchar(' ');
                current_state = NORMAL;
            }
            else if (ch == '*')
            {
                current_state = COMMENT_STAR;
            }
            else
            {
                current_state = COMMENT_BLOCK;
            }
            break;
        }   
    }
}