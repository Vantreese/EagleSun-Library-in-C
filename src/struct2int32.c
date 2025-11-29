/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
#include <esunlib.h>

Int32 Struct2Int32( void *data )

Date:   14 July 2000
Input:  *data: assumed to be of type (Int32_t*)
Return: (Int32) data->data, or 0 if data is NULL.
************************************************************************/

#include <esunlib.h>

Int32 Struct2Int32( void *data ) {
        Int32_t *idata = (Int32_t*) data;
        return (idata != NULL ? idata->data : 0);
}
