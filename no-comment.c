// no-comment.c
// Řešení IJC-DU1, příklad a), 22.3.2026
// Autor: Aldrin Joseph Sosa Dominguez, FIT
// Přeloženo: clang 17.0.0
// Program to delete the comments of a c file

#define _POSIX_C_SOURCE 200809L

#include "error.h"
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

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

    struct stat st_input, st_output;

    //fstat retrieves the information of the files using POSIX
    //fileno gets the file descriptor of the file
    if ((fstat(fileno(input), &st_input) == 0) && ((fstat(fileno(stdout), &st_output) == 0)))
    {
        //checks if they are file with the same inode(st_ino) and in the same device(st_dev)
        if ((st_input.st_ino == st_output.st_ino) && (st_input.st_dev == st_output.st_dev))
        {
            error_exit("The input and the output are the same\n");
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
            // don't write the slash until is safe to know that is a character and no a comment
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
            // finish the string
            if (ch == '\"')
            {
                current_state = NORMAL;
            }
            // start a escape character
            else if (ch == '\\')
            {
                current_state = ESCAPE_STRING;
            }
            break;
        case CHAR:
            putchar(ch);
            // finish the char 
            if (ch == '\'')
            {
                current_state = NORMAL;
            }
            // start a escape character
            else if (ch == '\\')
            {
                current_state = ESCAPE_CHAR;
            }
            break;
        case SLASH:
            // start a comment line
            if (ch == '/')
            {
                current_state = COMMENT_LINE;
            }
            // start a comment block
            else if (ch == '*')
            {
                current_state = COMMENT_BLOCK;
            }
            // start a string
            else if (ch == '\"')
            {
                putchar('/');
                putchar(ch);
                current_state = STRING;
            }
            // start a char
            else if (ch == '\'')
            {
                putchar('/');
                putchar(ch);
                current_state = CHAR;
            }
            // write the previus slash and the current char 
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
            // let the line comment be more than one line
            if (ch == '\\')
            {
                current_state = ESCAPE_COMMENT;
            }
            // if its the end of the line set a new line and go back to normal mode
            else if (ch == '\n')
            {
                putchar('\n');
                current_state = NORMAL;
            }
            break;
        case COMMENT_BLOCK:
            //be prepared to finish the comment block
            if (ch == '*')
            {
                current_state = COMMENT_STAR;
            }
            break;
        case COMMENT_STAR:
            //if the comment block end put a space and go back to normal mode
            if (ch == '/')
            {
                putchar(' ');
                current_state = NORMAL;
            }
            // in order to /******/ to work
            else if (ch == '*')
            {
                current_state = COMMENT_STAR;
            }
            // in order to /* * */ to work
            else
            {
                current_state = COMMENT_BLOCK;
            }
            break;
        }   
    }
    if (current_state == COMMENT_BLOCK || current_state == COMMENT_STAR)
    {
        error_exit("file finished in an uncompleted comment\n");
    }
    else if (current_state == ESCAPE_STRING || current_state == STRING)
    {
        error_exit("file finished in an uncompleted string\n");
    }
    else if (current_state == CHAR || current_state == ESCAPE_CHAR)
    {
        error_exit("file finished in an uncompleted char\n");
    }
    // if the last char was a slash write it
    else if (current_state == SLASH)
    {
        putchar('/');
    }
    if (input != stdin)
    {
        fclose(input);
    }
    
    return 0;
}
