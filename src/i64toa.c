/** PUBLIC i64toa() ****************************************
Input:  Int64 value, char *string, int radix;
Output: The value converted to an array of characters in the
        base of radix and put into *string.
Return: *string
==========================================================*/

#include "esundefs.h"

char *i64toa( Int64 value, char *string, int radix )
{
        int     i_l, i_r;
        Int64   i64_d;
        char    d;

        /* radix = (radix >= 0 ? radix : -radix); */
        i64_d = (value != 0 ? (value < 0 ? -value : value) : 1);
        for (i_r = 0; (i64_d > 0L) && (radix != 0); ++i_r)
        {
                i64_d /= (Int64) (radix > 0 ? radix : -radix);
        }
        string[0] = '+';
        if (value < 0L)
        {
                ++i_r;
                string[0] = '-';
        }
        string[i_r] = '\000';
        for (i_l = i_r - 1; (i_l >= (string[0] == '-')) && (radix != 0); --i_l)
        {
                i64_d = (Int64) (value % (radix > 0 ? radix : -radix));
                d = (char) (i64_d < 0L ? -i64_d : i64_d);
                string[i_l] = (d >= 10 ? (d + (radix > 0 ? 'a' : 'A') - 10) : (d + '0'));
                value /= (Int64) (radix > 0 ? radix : -radix);
        }

        return string;
}
