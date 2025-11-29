/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001
************************************************************************/

#include "dln.h"

Dln_t *dln_GetNodeSorted(Dln_t *dln, void *req,
        int (*GetFn)(void *, void *))
{
        int     stat;

        if (!req)
                return NULL;
        while (dln)
        {
                if((stat = GetFn(_Dln_Data(dln), req)) == 0)
                        return dln;
                dln = (stat > 0 ? NULL : _Dln_Next(dln));
        }
        return NULL;
}
