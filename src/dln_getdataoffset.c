/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001
************************************************************************/

#include "dln.h"

void *dln_GetDataOffset(Dln_t *dln, void *req,
                        int (*GetOffsetFn)(void *, void *, void **))
{
        int     ioffset;
        void    *out = NULL;
        if (!req)
                return NULL;
        while (dln)
        {
                if ((ioffset = GetOffsetFn(_Dln_Data(dln), req, &out)) == 0)
                        return out;
                dln = _Dln_Next(dln);
        }
        return NULL;
}
