/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001

Useful for deleting structures but preserving data contents, such as
when environmental variables were used.

************************************************************************/

#include "dln.h"

Dln_t *dln_Delete(Dln_t *dln)
{
        Dln_t   *hd = NULL, *p, *n;
        if (!dln)
                return NULL;
        hd = dln_Head(dln);
        p = _Dln_Previous(dln);
        n = _Dln_Next(dln);
        hd = (dln == hd ? n : hd);
        Dln_ReNext(p, n);
        Dln_RePrevious(n, p);
        free(dln);
        return hd;
}
