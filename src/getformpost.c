#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *GetFormPost( char env[] )
{
        char    szVar[BUFSIZ];
        char    *szEQ;

        if (!env)
                return NULL;
        strcpy(szVar, "VAR_");
        strcat(szVar, env);
        szEQ = getenv(szVar);
        return szEQ;
}
