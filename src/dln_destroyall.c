/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001
************************************************************************/

#include "dln.h"

Dln_t *dln_DestroyAll(Dln_t *dln, void (*FreeData)(void *))
{
        Dln_t   *n;
        dln = dln_Head(dln);
        while (dln)
        {
                n = dln_Destroy(dln, FreeData);
                dln = n;
        }
        return dln;
}
