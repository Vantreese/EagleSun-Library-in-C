/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001

Much cheaper approach to dln_GetDataOffset(dln, req, my_strstr)
with int my_strstr(char *p1, char *p2, char *out) making a call to
strstr().

************************************************************************/

#include <string.h>
#include "dln.h"

char *dln_MatchSZ(Dln_t *dln, const char *req)
{
        char    *out;
        if (!req)
                return NULL;
        while (dln)
        {
                out = strstr((const char*)_Dln_Data(dln), req);
                if(out)
                        return out;
                dln = _Dln_Next(dln);
        }
        return NULL;
}
