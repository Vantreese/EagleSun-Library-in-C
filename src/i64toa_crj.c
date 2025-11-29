/** PUBLIC i64toa_crj() ************************************
"Int64-to-Ascii Chop, Right-Justify"
Input:  Int64 value, char *string, int radix, int len;
Output: value is converted to an array of characters in the
        base of radix, to the maximum of len, and stored in
        *string.  Digits less than len are padded by space.
        If larger, the leftmost digits are chopped off.
Return: *string
==========================================================*/

#include "esundefs.h"

char *i64toa_crj( Int64 value, char *string, int radix, int len )
{
    int i;
    Int64 i64_d;
    char d;
    short s_r = 0;
    int first = (value < 0L ? -1 : 1);

    s_r = (radix == 0 ? -1 : (radix > 0 ? 1 : 0));
    radix = (radix > 0 ? radix : -radix);
    string[len] = '\000';
    for (i = len - 1; (s_r != -1) && (i >= 0); --i) {
        i64_d = (Int64) (value % radix);
        d = (char) (i64_d < 0 ? -i64_d : i64_d);
        if (value != 0 || i == len - 1) {
            string[i] = (d >= 10 ? (d + (s_r > 0 ? 'a' : 'A') - 10) : (d + '0'));
        } else {
            if (first == -1) string[i] = '-';
            else string[i] = ' ';
            first = 0;
        }
        value /= (Int64) radix;
    }

    return string;
}
