/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   14 March 2001
Input:  acsize: size of *ac; *ac: data attached into rawdata_t.
Action: Create structure for rawdata_t, load data into it.
Return: Node of rawdata_t.
************************************************************************/

#include <esunlib.h>

rawdata_t *Create_rawdata_t( size_t acsize, unsigned char *ac )
{
        rawdata_t       *ff = NULL;

        if (!ac)        return NULL;
        ff = calloc(1, sizeof(rawdata_t));
        if (!ff)        return NULL;
        ff->acsize = acsize;
        ff->ac = ac;
        return ff;
}
