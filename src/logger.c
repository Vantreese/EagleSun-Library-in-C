/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
*************************************************************************
*************************************************************************

#include <esunlib.h>

int Logger( time_t *Epoch, char *envp[] )

Date:
    23 May 2001

Input:
    *envp[]: Array of char*, in which the last element is NULL.

Output:
    *Epoch

Action:
    Write 1 line of data to a log file in Fields format.

Return:
    1: 1 line of log output; 0: no output; -1: error.

************************************************************************/

#include <string.h>
#include <esunlib.h>

int Logger( time_t *Epoch, char *envp[] )
{
    char    *szDate, szFileName[BUFSIZ], *sz;
    Field_t **Field;
    flFILE  *flLogger = NULL;
    size_t  loop, iFields;
    time_t  lEpoch;
    unsigned char   *ac;

    lEpoch = time(Epoch);
    szDate = ctime(&lEpoch);
    strlastchrNUL(szDate, '\n');
    fullname(szFileName, NULL, NULL, "log");
    flLogger = flopen(szFileName, "a+", 3, 0);
    if (!flLogger)
    {
        return -1;
    }
    rewind(flLogger->fp);
    for (iFields = 0; envp[iFields]; ++iFields);
    Field = calloc((iFields + 1), sizeof(Field_t));

    if (getc(flLogger->fp) == EOF)
    {
        for (loop = 0; loop < iFields; ++loop)
        {
            sz = envp[loop];
            ac = (unsigned char*) sz;
            Field[loop] = Create_rawdata_t(strlen(sz), ac);
        }
        ac = (unsigned char*) "Date";
        Field[iFields] = Create_rawdata_t(4, ac);
        fputFields(Field, iFields + 1, flLogger->fp);
        for (loop = 0; loop <= iFields; ++loop)
        {
            free(Field[loop]);
        }
    }
    rewind(flLogger->fp);

    for (loop = 0; loop < iFields; ++loop)
    {
        sz = getenv(envp[loop]);
        if (!sz) sz = "";
        ac = (unsigned char*) sz;
        Field[loop] = Create_rawdata_t(strlen(sz), ac);
    }
    ac = (unsigned char*) szDate;
    Field[iFields] = Create_rawdata_t(strlen(szDate), ac);
    fputFields(Field, iFields + 1, flLogger->fp);
    for (loop = 0; loop <= iFields; ++loop)
    {
        free(Field[loop]);
    }

    flclose(flLogger);
    return 1;
}
