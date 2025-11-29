/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001

Useful for deleting structures while preserving data, such as when
environmental variables are used.

************************************************************************/

#include "dln.h"

Dln_t *dln_DeleteAll(Dln_t *dln)
{
        Dln_t   *n;
        dln = dln_Head(dln);
        while (dln)
        {
                n = dln_Delete(dln);
                dln = n;
        }
        return dln;
}
