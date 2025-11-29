/** PUBLIC utoa() ******************************************
Input:  unsigned int value, char *string, int radix;
Output: The value converted to an array of characters in the
        base of radix and put into *string.
Return: *string
WARNING:        This function might be available in certain
        compilers.
==========================================================*/
char *utoa( unsigned int value, char *string, int radix )
{
    int i_l, i_r;
    unsigned int ui_d;
    char d;

    /* radix = (radix >= 0 ? radix : -radix); */
    ui_d = (value != 0 ? value : 1);
    for (i_r = 0; (ui_d > 0) && (radix != 0); ++i_r) {
        ui_d /= (unsigned int) (radix > 0 ? radix : -radix);
    }
    string[i_r] = '\000';
    for (i_l = i_r - 1; (i_l >= 0) && (radix != 0); --i_l) {
        ui_d = (unsigned int) (value % (radix > 0 ? radix : -radix));
        d = (char) ui_d;
        string[i_l] = (d >= 10 ? (d + (radix > 0 ? 'a' : 'A') - 10) : (d + '0'));
        value /= (unsigned int) (radix > 0 ? radix : -radix);
    }

    return string;
}

