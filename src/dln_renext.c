/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
************************************************************************/

#include "dln.h"

Dln_t *dln_ReNext(Dln_t *dln, Dln_t *next)
{
        Dln_ReNext(dln, next);
        return Dln_Next(dln);
}
