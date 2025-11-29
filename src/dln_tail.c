/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001
Input:  *dln
Action: Traverse to the tail of *dln list.
Return: The tail of *dln
************************************************************************/

#include "dln.h"

Dln_t *dln_Tail(Dln_t *dln)
{
        while (Dln_Next(dln))
                dln = _Dln_Next(dln);
        return dln;
}
