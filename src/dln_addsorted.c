/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001
Input:  *dln, *add, ComparFn(void*, void*)
Action: Put *add in sort-order of *dln list.
Return: The head of the list.
************************************************************************/

#include "dln.h"

Dln_t *dln_AddSorted(Dln_t *dln, Dln_t *add,
        int (*ComparFn)(void *, void *))
{
        Dln_t   *p, *q;
        if (!add)
                return dln_Head(dln);
        _Dln_RePrevious(add, NULL);
        _Dln_ReNext(add, NULL);
        if (!dln)
                return add;
        dln = dln_Head(dln);
        p = dln;
        q = add;
        while(ComparFn(_Dln_Data(p), _Dln_Data(q)) <= 0)
        {
                if(!_Dln_Next(p))
                {
                        _Dln_ReNext(p, q);
                        _Dln_RePrevious(q, p);
                        return dln;
                }
                p = _Dln_Next(p);
        }
        if(p == dln)
                dln = q;
        _Dln_ReNext(q, p);
        _Dln_RePrevious(q, _Dln_Previous(p));
        Dln_ReNext(_Dln_Previous(p), q);
        _Dln_RePrevious(p, q);
        return dln;
}
