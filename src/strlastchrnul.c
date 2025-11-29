/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
        #include <esunlib.h>

        char *strlastchrNUL(char str[], int c)

Date:   26 August 2000
Input:  str[] is a string constant, c is a character value.
Action: Compare c with the last character in str[] that precedes the 
        NUL; if found, convert the last character to NUL.
Return: If last character in str[] matches with c, pointer to the last
        position in str[] where the character was converted to a NUL;
        NULL if no match.
************************************************************************/

#include <string.h>
char *strlastchrNUL( char str[], int c ) {
        char    *chr = NULL;
        size_t  len;

        len = strlen(str);

        chr = (len == 0 ?
                NULL :
                (str[len - 1] == c ? &(str[len - 1]) : NULL));
        if(chr)
                chr[0] = '\000';

        return chr;
} 

