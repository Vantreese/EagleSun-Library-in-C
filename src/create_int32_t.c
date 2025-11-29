/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
#include <esunlib.h>

Int32_t *Create_Int32_t(Int32 i32)

Date:   5 July 2000
Input:  i32
Action: Allocate memory for an Int32_t structure, load it with i32.
Return: Pointer to (Int32_t) containing i32, or NULL if unable to
        allocate memory.
Special!!!      Create_Int32_t is a model fn() for loading structures
                of single elements, useful for compatibility with
                (void*) variables.
************************************************************************/

#include <esunlib.h>

Int32_t *Create_Int32_t(Int32 i32) {
        Int32_t *ni32 = malloc(sizeof(Int32_t));
        if(!ni32)
                return NULL;
        ni32->data = i32;
        return ni32;
}

