#include <stdio.h>

int fputLE(int c, FILE *Fp) {
        return( (fputc((0xff & c), Fp) & (~0xff00))
                | ((fputc((0xff & (c >> 8)), Fp) << 8) & (~0x00ff)) );
}

