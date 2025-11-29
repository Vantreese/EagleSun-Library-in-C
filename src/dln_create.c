/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001
Input:  *data
Action: Create a node with *data contents.
Return: Node containing *data.
************************************************************************/

#include "dln.h"

Dln_t *dln_Create(void *data)
{
        Dln_t   *dlnnew;
        if (!data)
                return NULL;
        dlnnew = malloc(sizeof(Dln_t));
        if (!dlnnew)
                return NULL;
        _Dln_ReData(dlnnew, data);
        _Dln_ReNext(dlnnew, NULL);
        _Dln_RePrevious(dlnnew, NULL);
        return dlnnew;
}
