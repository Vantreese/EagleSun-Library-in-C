#include <esunlib.h>


Dln_t *fgetsec( Dln_t *dln, size_t secsize, FILE *fp )
{
        Dln_t           *dln1;
        rawdata_t       *raw;
        size_t          size = 1, loops = 0;
        unsigned char   *ac;

        while (!feof(fp) && size)
        {
                ac = calloc(secsize, sizeof(unsigned char));
                size = fread(ac, sizeof(unsigned char), secsize, fp);
                if (size > 0)
                {
                        raw = Create_rawdata_t(size, ac);
                        dln1 = dln_Create(raw);
                        dln = dln_Add(dln, dln1);
                }
                else
                {
                        free(ac);
                }
        }
        return dln;
}

