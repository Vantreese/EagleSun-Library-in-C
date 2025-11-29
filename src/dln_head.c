/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001
Input:  *dln
Action: Traverse to the head of *dln.
Return: The head of *dln.
************************************************************************/

#include "dln.h"

Dln_t *dln_Head(Dln_t *dln)
{
        while (Dln_Previous(dln))
                dln = _Dln_Previous(dln);
        return dln;
}
