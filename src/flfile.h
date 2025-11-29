#ifndef _esunlib_flfile_defs_
#define _esunlib_flfile_defs_

#define LockSfx ".lock"

typedef struct {
        char *LockName;
        FILE *fp;
        int  fd;
} flFILE;

#endif
