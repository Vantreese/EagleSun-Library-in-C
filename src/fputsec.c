#include <esunlib.h>

size_t fputsec( Dln_t *dln, FILE *fp )
{
        Dln_t           *dln1 = dln;
        rawdata_t       *raw;
        size_t          size = 0;

        while (dln1)
        {
                raw = dln_Data(dln1);
                size += fwrite(raw->ac, sizeof(unsigned char), raw->acsize, fp);
                dln1 = dln_Next(dln1);
        }
        return size;
}
