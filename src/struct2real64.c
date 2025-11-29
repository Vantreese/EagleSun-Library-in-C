/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
#include <esunlib.h>

Real64 Struct2Real64( void *data )

Date:   14 July 2000
Input:  *data: assumed to be of type (Real64_t*)
Return: (Real64) data->data, or 0.0 if data is NULL.
************************************************************************/

#include <esunlib.h>

Real64 Struct2Real64( void *data ) {
        Real64_t        *rdata = (Real64_t*) data;
        return (rdata != NULL ? rdata->data : 0.0);
}
