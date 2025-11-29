/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
        #include <esunlib.h>

        char *strlastchr(char str[], int c)

Date:   18 August 2000
Input:  str[] is a string constant, c is a character.
Action: Compare c with the last character in str[] that precedes the NUL.
Return: If c matches to the last character in str[], pointer to the last
        character in str[]; or NULL if no match.
************************************************************************/

#include <string.h>
char *strlastchr( char str[], int c ) {
        size_t  len;

        len = strlen(str);

        return(len == 0 ?
                NULL :
                (str[len - 1] == c ? &(str[len - 1]) : NULL));
} 

