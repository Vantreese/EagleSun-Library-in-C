#include <string.h>

/*
Compare two arrays of characters, each possibly of different sizes.
Compare by value.
*/

int mem2cmp(const void *b1, size_t len1, const void *b2, size_t len2) {
        int     cmpsize, icmp;
        size_t  lenc;

        cmpsize = (len1 < len2 ? -1 : (len1 > len2 ? 1 : 0));
        lenc = (len1 < len2 ? len1 : len2);
        icmp = memcmp(b1, b2, lenc);

        return (icmp == 0 ? cmpsize : icmp);
}

