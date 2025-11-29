/* flclose.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <esconfig.h>
#include "flfile.h"

#if defined(sparc_Solaris_spro) || defined(ix86_Unix_gcc2) || defined(ix86_Win32_gcc2) || defined(sparc_Unix_gcc2)

#include <unistd.h>

int flclose(flFILE *flp)
{
        int i = 0;

        if (!flp)
                return EOF;
        if (flp->fp)
                i = fclose(flp->fp);
        if (flp->LockName)
        {
                ulockfile(flp->fd);
                free(flp->LockName);
                free(flp);
        }
        return i;
}

#elif defined(ix86_MSWin_msvc)

#include <io.h>

int flclose(flFILE *flp)
{
        int i = 0;

        if (!flp)
                return EOF;
        if (flp->fp)
                i = fclose(flp->fp);
        if (flp->LockName)
        {
                _unlink(flp->LockName);
                free(flp->LockName);
                free(flp);
        }
        return i;
}

#else

#error Unable to compile flclose() in flclose.c

#endif


/*

Previous Unix method equivalent to current Microsoft method.

#include <unistd.h>

int flclose(flFILE *flp)
{
        int i = 0;

        if (!flp)
                return EOF;
        if (flp->fp)
                i = fclose(flp->fp);
        if (flp->LockName)
        {
                unlink(flp->LockName);
                free(flp->LockName);
                free(flp);
        }
        return i;
}

*/
