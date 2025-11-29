/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001

Use this when *dln was not created by dln_AddSorted().  May also use
when needed to resort data.

************************************************************************/

#include "dln.h"

Dln_t *dln_Sort( Dln_t *dln, int (*ComparFn)(void *, void *) )
{
        Dln_t   *p0 = NULL, *p1, *p2;
        Dln_t   *q1 = dln, *q2;
        int     iCmp = 1;

        if (q1)
                p0 = q2 = _Dln_Next(dln);
        while (p0)
        {
                while (q1 && (ComparFn(_Dln_Data(p0), _Dln_Data(q1)) < 0))
                {
                        q2 = q1;
                        q1 = _Dln_Previous(q1);
                }
                if (q2 != p0)
                {
                        p1 = _Dln_Previous(p0);
                        p2 = _Dln_Next(p0);
                        Dln_ReNext(p1, p2);
                        Dln_RePrevious(p2, p1);
                        _Dln_RePrevious(p0, q1);
                        _Dln_ReNext(p0, q2);
                        Dln_ReNext(q1, p0);
                        Dln_RePrevious(q2, p0);
                        p0 = p1;
                        while (_Dln_Previous(dln))
                                dln = _Dln_Previous(dln);
                }
                q1 = p0;
                p0 = q2 = _Dln_Next(p0);
        }
        return dln;
}
