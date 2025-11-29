/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   06-Dec-2004
Input:  trans = {Text2Web/Web2Text/DB2Raw/Raw2DB}, *vv, vsize
Action: Calculate the amount of memory needed to support the converted
        data.
Return: Predicted size of the conversion.
************************************************************************/

#include <string.h>
#include <esunlib.h>
#include "fields.h"

#define AN              "0123456789-._ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define HexDigits       "0123456789ABCDEF"

size_t predictsize( int trans, void *vv, size_t vsize )
{
        char            *sz, HD[3] = {NUL, NUL, NUL};
        char            BackCmd[] = {_dbf_Cmd, _dbf_Cmd, NUL};
        char            BackFS[] = {_dbf_Cmd, _dbf_FS, NUL};
        char            BackRS[] = {_dbf_Cmd, _dbf_RS, NUL};
        int             iCmd = 0;
        size_t          size = 0, i;
        unsigned char   *ac;
	int             idbf_type;


        switch (trans)
        {
        case Text2Web:  /*  Usually larger than *sz  */
                if (vv)
                {
                        sz = (char*) vv;
                        for (i = 0; sz[i] != NUL; ++i)
                        {
                                if(!strchr(AN, sz[i]))
                                        size += 3;
                                else
                                        ++size;
                        }
                }
                ++size;
                break;
        case Web2Text:  /*  Usually smaller than *sz  */
                if (vv)
                {
                        sz = (char*) vv;
                        for (i = 0; sz[i] != NUL; ++i)
                        {
                                switch (sz[i])
                                {
                                case '%':
                                        ++size;
                                        i += 2;
                                        break;
                                default:
                                        ++size;
                                        break;
                                }
                        }
                }
                ++size;
                break;
        case DB2Raw:
                if (vv)
                {
                        sz = (char*) vv;
                        for (i = 0; sz[i]; ++i)
                        {
                                if (iCmd)
                                {
                                        if (strchr(HexDigits, sz[i]))
                                        {
                                                str0catc(HD, sz[i]);
                                                if (strlen(HD) == 2)
                                                {
                                                        ++size;
                                                        HD[0] = NUL;
                                                        iCmd = 0;
                                                }
                                        }
                                        else
                                        {
                                                if (strlen(HD) > 0)
                                                {
                                                        ++size;
                                                        if (HD[1])
                                                                ++size;
                                                }
                                                ++size;
                                                iCmd = 0;
                                        }
                                }
                                else
                                {
					idbf_type = dbf_whattype(sz[i]);
                                        switch (idbf_type)
                                        {
                                        case DBF_Cmd_Type:
                                                iCmd = 1;
                                                break;
                                        case DBF_FS_Type:
                                                return size;
                                        case DBF_RS_Type:
                                                return size;
                                        default:
                                                ++size;
                                                break;
                                        }
                                }
                        }
                }
                break;
        case Raw2DB:
                if (vv)
                {
                        ac = (unsigned char*) vv;
                        for (i = 0; i < vsize; ++i)
                        {
                                switch (ac[i])
                                {
                                case '\n':
                                        size += 2;
                                        break;
                                case '\r':
                                        size += 2;
                                        break;
                                case '\t':
                                        size += 2;
                                        break;
                                case '\0':
                                        size += 2;
                                        break;
                                default:
					idbf_type = dbf_whattype(ac[i]);
                                        switch (idbf_type)
                                        {
                                        case DBF_Cmd_Type:
                                                size += strlen(BackCmd);
                                                break;
                                        case DBF_FS_Type:
                                                size += strlen(BackFS);
                                                break;
                                        case DBF_RS_Type:
                                                size += strlen(BackRS);
                                                break;
                                        default:
                                                if (ac[i] < ' ' || ac[i] >= 127)
                                                {
                                                        size += 3;
                                                }
                                                else
                                                {
                                                        ++size;
                                                }
                                        }
                                }
                        }
                }
                ++size;
                break;
        default:
                break;
        }

        return size;
}
