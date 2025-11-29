#include <stdio.h>

int fgetBE(FILE *Fp) {
        return( ((fgetc(Fp) << 8) & (~0x00ff)) | (fgetc(Fp) & (~0xff00)) );
}

