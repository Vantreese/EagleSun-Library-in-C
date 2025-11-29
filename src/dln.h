/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001

Double-linked list nodes

************************************************************************/

#ifndef _esunlib_dln_h_
#define _esunlib_dln_h_

#include "esunlib.h"

#define _Dln_Next(dln)          (dln)->next
#define _Dln_Previous(dln)      (dln)->prev
#define _Dln_Data(dln)          (dln)->data
#define _Dln_ReNext(dln, n)     ((dln)->next = (n))
#define _Dln_RePrevious(dln, p) ((dln)->prev = (p))
#define _Dln_ReData(dln, d)     ((dln)->data = (d))

#define Dln_Next(dln)           ((dln) != NULL ? _Dln_Next(dln) : NULL)
#define Dln_Previous(dln)       ((dln) != NULL ? _Dln_Previous(dln) : NULL)
#define Dln_Data(dln)           ((dln) != NULL ? _Dln_Data(dln) : NULL)
#define Dln_ReNext(dln, n)      { if(dln) _Dln_ReNext(dln, n); }
#define Dln_RePrevious(dln, p)  { if(dln) _Dln_RePrevious(dln, p); }
#define Dln_ReData(dln, d)      { if(dln) _Dln_ReData(dln, d); }

#endif
