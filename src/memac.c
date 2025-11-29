#include <string.h>

void *memac(const void *b, size_t lenb, const void *ac, size_t lenac) {
        char    *c = (char*) ac;
        int     cmp;
        void    *chr = NULL;

        if((lenac == 0) || (lenac > lenb)) {
                return (void*) b;
        }

        chr = memchr(b, *c, (lenb - lenac + 1));
        if(chr)
                cmp = memcmp(chr, ac, lenac);

        return(cmp == 0 ? chr : NULL);
}

