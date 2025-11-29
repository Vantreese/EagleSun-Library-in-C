/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001

Preserves data and structure, separates node from the list.

************************************************************************/

#include "dln.h"

void *dln_Hide(Dln_t *dln)
{
        Dln_t   *hd = NULL, *p, *n;

        if(!dln)
                return NULL;
        hd = dln_Head(dln);
        p = _Dln_Previous(dln);
        n = _Dln_Next(dln);
        hd = (hd == dln ? n : hd);
        Dln_ReNext(p, n);
        Dln_RePrevious(n, p);
        _Dln_ReNext(dln, NULL);
        _Dln_RePrevious(dln, NULL);
        return hd;
}
