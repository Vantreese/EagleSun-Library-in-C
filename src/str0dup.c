/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
        #include <esunlib.h>

        char *str0dup(str[])

Date:   18 August 2000
Input:  str[]: string.
Action: If str[] is not NULL, use strdup() to allocate new memory and
        copy str[] into the new memory space.
Return: 1:      if str[] != NULL, str0dup() = pointer to the copy of
                str[];
        2:      NULL if str[] == NULL;
        3:      NULL if unable to allocate new memory via the strdup().
************************************************************************/

#include <string.h>

char *str0dup( char str[] ) {
        return(str == NULL ? NULL : strdup(str));
}

