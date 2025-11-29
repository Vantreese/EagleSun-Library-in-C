/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
#include <esunlib.h>

Real64_t *Create_Real64_t(Real64 r64)

Date:   5 July 2000
Input:  r64
Action: Allocate memory for a Real64_t structure, load r64 into it.
Return: Pointer to (Real64_t*) containing r64, or NULL if unable to
        allocate memory.
Special!!!      Create_Real64_t is a model fn() for loading structures
                of single elements, useful for compatibility with
                (void*) variables.
************************************************************************/

#include <esunlib.h>

Real64_t *Create_Real64_t(Real64 r64) {
        Real64_t        *nr64 = malloc(sizeof(Real64_t));
        if(!nr64)
                return NULL;
        nr64->data = r64;
        return nr64;
}

