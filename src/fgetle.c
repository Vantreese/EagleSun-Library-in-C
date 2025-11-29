#include <stdio.h>

int fgetLE(FILE *Fp) {
        return( (fgetc(Fp) & (~0xff00)) | ((fgetc(Fp) << 8) & (~0x00ff)) );
}

