/* flopen.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <esconfig.h>
#include "flfile.h"

/*

  Allow multiple read-only access or one write-access

  To explore... the possibility of using
    fld = lockfile(path, mode, timeout);
  by accident observed possibilities with this method.

*/

#if defined(sparc_Solaris_spro) || defined(ix86_Unix_gcc2) || defined(ix86_Win32_gcc2) || defined(sparc_Unix_gcc2)

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

flFILE *flopen(const char *path, const char *mode, int duration, int reserved) {
    char            szLock[BUFSIZ];
    FILE            *fp;
    flFILE          *flp = NULL;
    int             fld;
    unsigned int    timeout = (unsigned int) duration;
    struct stat     statbuf;

    if (!path || !mode)
        return NULL;
    strcpy(szLock, path);
    strcat(szLock, LockSfx);
    if (strchr(mode, 'a') || strchr(mode, 'w'))
    {
        fld = lockfile(szLock, mode, timeout);
    }
    else
    {
        if (!stat(path, &statbuf))
        {
            fld = lockfile(szLock, mode, timeout);
        }
        else
        {
            fld = -1;
        }
    }

    if (fld == -1)
    {
        return NULL;
    }

    fp = fopen(path, mode);
    if (fp)
    {
        flp = malloc(sizeof(flFILE));
        flp->fp = fp;
        flp->LockName = strdup(szLock);
        flp->fd = fld;
    }
    else
    {
        ulockfile(fld);
    }
    return flp;
}

#elif defined(ix86_MSWin_msvc)

#include <fcntl.h>
#include <io.h>
#include <sys/stat.h>
#include <Wtypes.h>
#include <winbase.h>

flFILE *flopen(const char *path, const char *mode, int duration, int reserved) {
        char            szLock[BUFSIZ], szBuf[BUFSIZ];
        DWORD           dw1second = (DWORD) 1000;
        FILE            *fp;
        flFILE          *flp = NULL;
        int             fld, retryopen = 0, ireadwrite, icheckrw = 1;
        unsigned int    len;

        if (!path || !mode)
                return NULL;
        if (strchr(mode, 'a') || strchr(mode, 'w') || strchr(mode, '+')) {
                ireadwrite = 1;
        } else {
                ireadwrite = 0;
        }
        strcpy(szLock, path);
        strcat(szLock, LockSfx);
        while (((fld = _open(szLock, (_O_CREAT | _O_EXCL | _O_WRONLY), 
                (_S_IREAD | _S_IWRITE))) == -1) && (retryopen <= duration)
                && icheckrw) {
                if (ireadwrite) {
                        if (retryopen < duration)       SleepEx(dw1second, FALSE);
                        ++retryopen;
                } else {
                        fld = _open(szLock, (_O_RDONLY));
                        if (fld != -1) {
                                _read(fld, szBuf, BUFSIZ);
                                if (szBuf[0] == '*') {
                                        icheckrw = 1;
                                } else {
                                        icheckrw = 0;
                                }
                        }
                        if (icheckrw || (fld == -1)) {
                                if (retryopen < duration)       SleepEx(dw1second, FALSE);
                                ++retryopen;
                        }
                        if (fld != -1) {
                                _close(fld);
                                fld = -1;
                        }
                }
        }
        if ((fld == -1) && (ireadwrite || icheckrw)) {
                return NULL;
        }
        if (ireadwrite) {
                _write(fld, "*", 1);
        }
        if (fld != -1) {
                len = (unsigned int) strlen(path);
                _write(fld, path, len);
                _close(fld);
        }

        fp = fopen(path, mode);
        if (fp) {
                flp = malloc(sizeof(flFILE));
                flp->fp = fp;
                if (fld != -1) {
                        flp->LockName = strdup(szLock);
                }
                else {
                        flp->LockName = NULL;
                }
        } else {
                if (fld != -1) {
                        _unlink(szLock);
                }
        }
    return flp;
}

#else

#error Unable to compile flopen() in flopen.c

#endif

/* Historical version

FILE *flopen(const char *path, const char *mode) {
    FILE *fp, *fpLock;
    char szLock[BUFSIZ];
    int iMkLock = 0;
    time_t tlock;

    strcpy(szLock, path); strcat(szLock, LockSfx);

    If file is locked by another process, then wait till released.
    fpLock = fopen(szLock, "r");
    while (fpLock) {
        fread(&tlock, sizeof(time_t), 1, fpLock);
        fclose(fpLock);
        fpLock = fopen(szLock, "r");
    }

    Create lock file if open for any kind of writing.
    if (strchr(mode, 'a') || strchr(mode, 'w') || strchr(mode, '+')) {
        if ((fpLock = fopen(szLock, "w")) != NULL) {
            time(&tlock);
            fwrite(&tlock, sizeof(time_t), 1, fpLock);
            fclose(fpLock);
        }
    }

    Clearance to open file
    fp = fopen(path, mode);

    return fp;
}


The below is a later Unix version equivalent to the current Microsoft version.

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

flFILE *flopen(const char *path, const char *mode, int duration, int reserved) {
        char            szLock[BUFSIZ], szBuf[BUFSIZ];
        FILE            *fp;
        flFILE          *flp = NULL;
        int             fld, retryopen = 0, ireadwrite, icheckrw = 1;
        unsigned int    len;

        if (!path || !mode)
                return NULL;
        if (strchr(mode, 'a') || strchr(mode, 'w') || strchr(mode, '+')) {
                ireadwrite = 1;
        } else {
                ireadwrite = 0;
        }
        strcpy(szLock, path);
        strcat(szLock, LockSfx);
        while (((fld = open(szLock, (O_CREAT | O_EXCL | O_WRONLY), 
                (S_IREAD | S_IWRITE))) == -1) && (retryopen <= duration)
                && icheckrw) {
                if (ireadwrite) {
                        if (retryopen < duration)       sleep(1);
                        ++retryopen;
                } else {
                        fld = open(szLock, (O_RDONLY));
                        if (fld != -1) {
                                read(fld, szBuf, BUFSIZ);
                                if (szBuf[0] == '*') {
                                        icheckrw = 1;
                                } else {
                                        icheckrw = 0;
                                }
                        }
                        if (icheckrw || (fld == -1)) {
                                if (retryopen < duration)       sleep(1);
                                ++retryopen;
                        }
                        if (fld != -1) {
                                close(fld);
                                fld = -1;
                        }
                }
        }
        if ((fld == -1) && (ireadwrite || icheckrw)) {
                return NULL;
        }
        if (ireadwrite) {
                write(fld, "*", 1);
        }
        if (fld != -1) {
                len = (unsigned int) strlen(path);
                write(fld, path, len);
                close(fld);
        }

        fp = fopen(path, mode);
        if (fp) {
                flp = malloc(sizeof(flFILE));
                flp->fp = fp;
                if (fld != -1) {
                        flp->LockName = strdup(szLock);
                }
                else {
                        flp->LockName = NULL;
                }
        } else {
                if (fld != -1) {
                        unlink(szLock);
                }
        }
    return flp;
}

*/
