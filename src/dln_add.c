/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   24 January 2001
Input:  *dln, *add
Action: Put *add at the end of *dln
Return: The head of the list.
************************************************************************/

#include "dln.h"

Dln_t *dln_Add(Dln_t *dln, Dln_t *add)
{
        Dln_t   *tl = NULL;
        tl = dln_Tail(dln);
        Dln_ReNext(tl, add);
        Dln_RePrevious(add, tl);
        dln = (dln == NULL ? add : dln_Head(dln));
        return dln;
}
