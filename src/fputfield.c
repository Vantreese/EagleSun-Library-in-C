/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:	06-Dec-2004
************************************************************************/

#include <string.h>
#include <esunlib.h>
#include "fields.h"

void fputField( Field_t *Field, FILE *fp )
{
        char            Hex[4] = {'\\', NUL, NUL, NUL}, *szOut;
        char            BackCmd[] = {_dbf_Cmd, _dbf_Cmd, NUL};
        char            BackFS[] = {_dbf_Cmd, _dbf_FS, NUL};
        char            BackRS[] = {_dbf_Cmd, _dbf_RS, NUL};
        int             dc;
	int             idbf_type;
        size_t          asize, iLoop;
        unsigned int    dl;


        if (!Field || !fp)      return;

        asize = predictsize(Raw2DB, Field->ac, Field->acsize);
        szOut = calloc(asize, sizeof(char));
        for (iLoop = 0; (iLoop < Field->acsize) && Field->ac; ++iLoop)
        {
                dc = (int) Field->ac[iLoop];
                switch (dc)
                {
                case '\n':
                        strcat(szOut, "\\n");
                        break;
                case '\r':
                        strcat(szOut, "\\r");
                        break;
                case '\t':
                        strcat(szOut, "\\t");
                        break;
                case '\0':
                        strcat(szOut, "\\0");
                        break;
                default:
			idbf_type = dbf_whattype(dc);
                        switch (idbf_type)
                        {
                        case DBF_Cmd_Type:
                                strcat(szOut, BackCmd);
                                break;
                        case DBF_FS_Type:
                                strcat(szOut, BackFS);
                                break;
                        case DBF_RS_Type:
                                strcat(szOut, BackRS);
                                break;
                        default:
                                if ((dc < ' ') || (dc >= 127))
                                {
                                        dl = (unsigned int) dc;
                                        utoa_c0f(dl, &(Hex[1]), -16, 2);
                                        strcat(szOut, Hex);
                                }
                                else
                                {
                                        strcatc(szOut, dc);
                                }
                                break;
                        }
                        break;
                }
        }
        fputs(szOut, fp);
        free(szOut);
}

