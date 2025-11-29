char hex2char(char hex[2])
{
        char c = 0;

        if (!hex) {
                return (char) 0;
        }

        if (hex[0] != 0) {
                c = (hex[0] >= '0' && hex[0] <= '9' ?
                        hex[0] - '0' : hex[0] - 'A' + 10) << 4;
        }
        if (hex[1] != 0) {
                c |= (hex[1] >= '0' && hex[1] <= '9' ?
                        hex[1] - '0' : hex[1] - 'A' + 10);
        }
        return c;
}
