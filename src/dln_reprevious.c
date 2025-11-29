/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
************************************************************************/
#include "dln.h"

Dln_t *dln_RePrevious(Dln_t *dln, Dln_t *prev)
{
        Dln_RePrevious(dln, prev);
        return Dln_Previous(dln);
}
