/** PUBLIC utoa_crj() **************************************
"Unsigned-int-to-Ascii Chop, Right-Justify"
Input:  unsigned int value, char *string, int radix, int len;
Output: value is converted to an array of characters in the
        base of radix, to the maximum of len, and stored in
        *string.  Digits less than len are padded by space.
        If larger, the leftmost digits are chopped off.
Return: *string
==========================================================*/
char *utoa_crj( unsigned int value, char *string,
        int radix, int len )
{
    int i;
    unsigned int ui_d;
    char d;
    short s_r = 0;

    s_r = (radix == 0 ? -1 : (radix > 0 ? 1 : 0));
    radix = (radix >= 0 ? radix : -radix);
    string[len] = '\000';
    for (i = len - 1; (s_r != -1) && (i >= 0); --i) {
        ui_d = (unsigned int) (value % radix);
        d = (char) ui_d;
        if (value > 0 || i == len - 1) {
            string[i] = (d >= 10 ? (d + (s_r > 0 ? 'a' : 'A') - 10) : (d + '0'));
        } else {
            string[i] = ' ';
        }
        value /= (unsigned int) radix;
    }

    return string;
}

