/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                   http://www.eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************

Date:   2 July 2000
Input:  *dln, *fp
Action: Write the data contents of *dln to *fp; assuming that the data
        contents are of type (char*).
Return: The amount of data written to *fp; EOF if error writing.
************************************************************************/

#include <esunlib.h>

int fputss(Dln_t *dln, FILE *fp) {
        Dln_t   *p1 = dln;
        int     iout = 0, ioutss = 0;

        while(p1 && iout != EOF) {
                iout = fputs((char*) dln_Data(p1), fp);
                ioutss += iout;
                p1 = dln_Next(p1);
        }

        return(iout == EOF ? EOF : ioutss);
}
