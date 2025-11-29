#include <stdio.h>

int fputBE(int c, FILE *Fp) {
        return( ((fputc((0xff & (c >> 8)), Fp) << 8) & (~0x00ff))
                | (fputc((0xff & c), Fp) & (~0xff00)) );
}

