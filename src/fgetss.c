/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                   http://www.eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
#include <esunlib.h>

Dln_t *fgetss(Dln_t *dln, FILE *fp)

Date:   9 May 2000
Input:  *dln, *fp
Action: Read *fp, build linked list of *dln by using fgets() repeatedly
        until encounter '\n' or EOF; very useful when reading one line
        text of unknown (possibly large) size.
Return: The head of the *dln list; head of new list, if *dln is NULL.
************************************************************************/

#include <string.h>
#include <esunlib.h>

/*
Similarly to fgets(), yet read one line of UNKNOWN size, terminated by
'\n' or EOF.
*/
Dln_t *fgetss(Dln_t *dln, FILE *fp) {
        int     iRead = 1;
        char    *sz1, szLine[BUFSIZ];
        size_t  size;
        Dln_t   *new;

        do {
                if(fgets(szLine, BUFSIZ, fp)) {
                        size = strlen(szLine);
                        if(szLine[size - 1] == '\n')    iRead = 0;
                        if(size < (BUFSIZ - 1)) iRead = 0;
                        sz1 = strdup(szLine);
                        new = dln_Create(sz1);
                        dln = dln_Add(dln, new);
                } else {
                        iRead = 0;
                }
        } while(iRead);

        return dln;
}
