/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
        #include <esunlib.h>

        char *str0dupz(str[])

Date:   28 August 2000
Input:  str[]: string.
Action: If str[] is not NULL, use strdup() to allocate new memory and
        copy str[] into the new memory space; otherwise, use strdup() to
        copy "".
Return: 1:  if str[] != NULL, str0dupz() = pointer to the copy of str[];
        2:  copy of "" if str[] == NULL;
        3:  NULL if unable to allocate new memory via the strdup().
************************************************************************/

#include <string.h>

char *str0dupz( char str[] ) {
    return(str == NULL ? strdup("") : strdup(str));
}

