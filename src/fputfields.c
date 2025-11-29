/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:	06-Dec-2004
Input:  **Fields, NumFields, *fp
Output: 
Action: Write 1 row of Field_t data to db file.
************************************************************************/

#include <esunlib.h>
#include "fields.h"

void fputFields( Field_t **Fields, size_t NumFields, FILE *fp )
{
        Field_t         *Field;
        size_t          iLoop;

        if (!Fields || (NumFields == 0) || !fp) return;
        for (iLoop = 0; (iLoop < NumFields) && Fields[iLoop]; ++iLoop) {
                Field = Fields[iLoop];
                if (iLoop > 0) {
                        putc((int)_dbf_FS, fp);
                }
                fputField(Field, fp);
        }
        putc((int)_dbf_RS, fp);
}
