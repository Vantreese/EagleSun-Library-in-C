/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
#include <esunweb.h>

char *getWebDat(char *toText, size_t *posEq, char FromWeb[])

Date:   30 November 2000
Input:  fromWeb[];
Output: If *toText is not NULL, results also copied into *toText;
        *posEq marks the position of the first "=".
Action:
    1.  fromWeb[] contains data extracted by the web server in raw
        format.  fromWeb[] is copied in this function for multiple
        calls.
    2.  The conversion rules to plain readable text format.
        a.  The (+) convert to SP.
        b.  The (%) indicates hexadecimal values of range 00, FF;
            will convert to appropriate text value.
        c.  The (&) indicates separating of parameters.
        d.  The (=) is the equivalence symbol between parameter names
            and the values of the parameters.
    3.  *posEq gives the position of the first "=".
Return: char *
    1.  *dest contains the results of converted data separated by
        (&).  Subsequent calls with fromWeb[] == NULL returns
        subsequent data separated by (&), until end of the data.
Note:   This is based on observable experience, and is probably not
        a complete conversion.
Note2:  After 2 years of observation, no errors have appeared.
Note3:  Recently modified with this spec: fromWeb[] is duplicated into
        a new memory location and saved.  When all the data is used up,
        the saved data will be destroyed.
************************************************************************/

#include <string.h>
#include <esunlib.h>

char *getWebDat(char *toText, size_t *posEq, char fromWeb[])
{
        size_t iFW = 0, ides = 0;
        char cDat;
        static char *src = NULL, *src0 = NULL;
        char *dest = toText, *last;
        int foundEq = 0;


        *posEq = 0;

        if (fromWeb != NULL) {
                if (src0) {
                        free(src0);
                }
                src0 = strdup(fromWeb);
                src = src0;
        }

        if (src == NULL) {
                return NULL;
        }

        last = strchrNUL(src, '&');

        if (!dest) {
                ides = predictsize(Web2Text, src, 1);
                dest = calloc(ides, sizeof(char));
                ides = 0;
        }

        while (src[iFW] != NUL) {
                if (!foundEq) ++*posEq;
                switch (src[iFW]) {
                case '=':
                        dest[ides++] = src[iFW++];
                        foundEq = 1;
                        break;
                case '+':
                        iFW++;
                        dest[ides++] = ' ';
                        break;
                case '%':
                        iFW++;
                        cDat = hex2char(&(src[iFW]));
                        iFW += 2;
                        dest[ides++] = cDat;
                        break;
                default:
                        dest[ides++] = src[iFW++];
                        break;
                }
        }

        if (last != NULL) {
                src = &(last[1]);
        } else {
                src = NULL;
                free(src0);
                src0 = NULL;
        }

        if (!foundEq) *posEq = 0;
        dest[ides] = NUL;
        return dest;
}

