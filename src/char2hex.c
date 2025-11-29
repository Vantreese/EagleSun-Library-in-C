#include <esunlib.h>

char *char2hex(char hex[3], char c)
{
        utoa_c0f((unsigned int) c, hex, -16, 2);
        return hex;
}
