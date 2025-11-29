/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   2 January 2001
************************************************************************/

#include "dln.h"

void *dln_Modify(Dln_t *dln, void (*FreeData)(void *), void *data)
{
        if (!dln || !data)
                return NULL;
        if (_Dln_Data(dln) != data)
        {
                FreeData(_Dln_Data(dln));
                _Dln_ReData(dln, data);
        }
        return _Dln_Data(dln);
}
