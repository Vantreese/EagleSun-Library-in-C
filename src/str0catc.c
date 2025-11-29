/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
        #include <esunlib.h>

        char *str0catc( char str[], int c )

Date:   18 August 2000
Input:  str[] is a string, c is a character value.
Output: str[] is appended with c as the last character.
Action: If str[] is not NULL, append c at the end of str[].
Return: str[]; or NULL if str[] is NULL.
************************************************************************/

#include <string.h>

char *str0catc( char str[], int c ) {
        char catc[2];

        if (!str) {
                return NULL;
        }
        catc[0] = (char) c;
        catc[1] = '\000';

        return(strcat(str, catc));
}

