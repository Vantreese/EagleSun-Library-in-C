/************************************************************************
                            EagleSun Library
                (c) 2000, 2001, 2002 Terry Ron Vantreese
************************************************************************/
/************************************************************************

Date:	14-Mar-2001
Update:	06-Dec-2004
Input:  *fp
Output: *iStat: error results.
Action: Load 1 field of data from a db file into a structured memory.
Return: Pointer to 1 field of data loaded into memory.
************************************************************************/

#include <string.h>
#include <esunlib.h>
#include "fields.h"

#define HexDigits "0123456789ABCDEF"


#define DBF_error       -1
#define DBF_endfile     0
#define DBF_endrec      1
#define DBF_newfield    2
Field_t *fgetField( int *iStat, FILE *fp )
{
    const int       dbf_error = DBF_error, dbf_endfile = DBF_endfile;
    const int       dbf_endrec = DBF_endrec, dbf_newfield = DBF_newfield;
    char            HD[3] = {'\0', '\0', '\0'};
    Field_t         *ff = NULL;
    int             iData, iCmd = 0;
    int             idbf_type;
    size_t          acsize = 0, msize = BUFSIZ;
    unsigned char   *ac, *ac0;

    if (!fp)
    {
        *iStat = dbf_endfile;
        return NULL;
    }
    iData = getc(fp);
    if (feof(fp))
    {
        *iStat = dbf_endfile;
        return NULL;
    }
    ac = calloc(BUFSIZ, sizeof(unsigned char));
    if (!ac)
    {
        *iStat = dbf_error;
        return NULL;
    }
    while (!feof(fp))
    {
        if((acsize + 3) >= msize)
        {
            msize += BUFSIZ;
            ac0 = calloc(msize, sizeof(unsigned char));
            if(!ac0)
            {
                free(ac);
                *iStat = dbf_error;
                return NULL;
            }
            memcpy(ac0, ac, (msize - BUFSIZ));
            free(ac);
            ac = ac0;
        }
        if(iCmd)
        {
            if (strchr(HexDigits, iData))
            {
                str0catc(HD, iData);
                if(strlen(HD) == 2)
                {
                    ac[acsize++] = hex2char(HD);
                    HD[0] = '\0';
                    iCmd = 0;
                }
            }
            else
            {
                if (strlen(HD) > 0)
                {
                    ac[acsize++] = HD[0];
                    if(HD[1]) ac[acsize++] = HD[1];
                }
                switch(iData)
                {
                case 'n':
                    ac[acsize++] = '\n';
                    break;
                case 'r':
                    ac[acsize++] = '\r';
                    break;
                case 't':
                    ac[acsize++] = '\t';
                    break;
                case '0':
                    ac[acsize++] = '\0';
                    break;
                default:
                    ac[acsize++] = (unsigned char) iData;
                    break;
                }
                iCmd = 0;
            }
        }
        else
        {
	    idbf_type = dbf_whattype(iData);
            switch (idbf_type)
            {
            case DBF_Cmd_Type:
                iCmd = 1;
                break;
            case DBF_FS_Type:
                *iStat = dbf_newfield;
                ff = Create_rawdata_t(acsize, ac);
                return ff;
            case DBF_RS_Type:
                *iStat = dbf_endrec;
                ff = Create_rawdata_t(acsize, ac);
                return ff;
            default:
                if ((iData >= 32) && (iData < 127))
                {
                    ac[acsize++] = (unsigned char) iData;
                }
                /*
                else
                {
                    Not supposed to be here anyways.
                }
                */
                break;
            }
        }
        iData = getc(fp);
    }
    ff = Create_rawdata_t(acsize, ac);
    *iStat = dbf_error;
    return ff;
}
