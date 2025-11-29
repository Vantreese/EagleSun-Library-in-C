/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001
************************************************************************/

#include "dln.h"

Dln_t *dln_Destroy(Dln_t *dln, void (*FreeData)(void *))
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
        FreeData(_Dln_Data(dln));
        free(dln);
        return hd;
}
