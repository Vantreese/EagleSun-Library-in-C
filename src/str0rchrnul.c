/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
        #include <esunlib.h>

        char *str0rchrNUL(char str[], int c)

Date:   18 August 2000
Input:  str[]: string; c: character value
Output: Last matching character in str[] to c converted to NUL.
Action: Scan str[] until the last occurrence of c in str[], if found,
        convert to NUL.
Return: 1:      pointer to str if found matching character in str[] to c;
        2:      NULL if no match.
        3:      NULL, if str[] is NULL.
************************************************************************/

#include <string.h>

char *str0rchrNUL( char str[], int c ) {
        char *chr;

        if(!str) {
                return NULL;
        }
        chr = strrchr(str, c);
        if(chr)
                chr[0] = '\000';

        return chr;
}

