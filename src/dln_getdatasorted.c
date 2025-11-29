/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001
************************************************************************/

#include "dln.h"

void *dln_GetDataSorted(Dln_t *dln, void *req, 
        int (*GetDataFn)(void *, void *))
{
        dln = dln_GetNodeSorted(dln, req, GetDataFn);
        return Dln_Data(dln);
}
