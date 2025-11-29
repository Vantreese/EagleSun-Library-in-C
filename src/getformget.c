#include <string.h>
#include "esunweb.h"

char *GetFormGet( char env[] )
{
        char    *var, *eq, szBuf1[BUFSIZ], *ret;
        int     nomatch = 0;
        size_t  poseq;

        if (!env) {
                return NULL;
        }

        var = getWebDat(szBuf1, &poseq, getenv("QUERY_STRING"));
        if (var) {
                if (poseq) {
                        var[poseq - 1] = NUL;
                }
                eq = &(var[poseq]);
                nomatch = strcmp(env, var);
        } else {
                nomatch = 0;
                eq = NULL;
        }
        while (nomatch) {
                var = getWebDat(szBuf1, &poseq, NULL);
                if (var) {
                        if (poseq) {
                                var[poseq - 1] = NUL;
                        }
                        eq = &(var[poseq]);
                        nomatch = strcmp(env, var);
                } else {
                        nomatch = 0;
                        eq = NULL;
                }
        }
        ret = (eq ? strdup(eq) : NULL);
        return ret;
}
