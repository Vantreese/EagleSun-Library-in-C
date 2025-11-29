/************************************************************************
                            EagleSun Library
                   (c) 2000, 2001 Terry Ron Vantreese
************************************************************************/
/************************************************************************
#include <esunlib.h>

void *Query(int expected, void *answer, size_t size, 
         void *dft, char *question)

Date:   2 December 2001
Input:
    size: maximum length of char*, or if 0, determined by user.
    sdefault: Default;
    question: The statement to give the user when asking for input.
Output: answer: User response.
Return: pointer to *answer, or allocate new memory if *answer is NULL.
************************************************************************/

#include <string.h>
#include <esunlib.h>

char *szQuery( char *answer, size_t size, char *sdefault,
              char *question )
{
    char    localA[BUFSIZ];
    char    *szA = answer;

    if (!question) return NULL;

    fprintf(stdout, "%s ", question);
    if (sdefault)
    {
        if (strlen(sdefault))
        {
            fprintf(stdout, "[%s] ", sdefault);
        }
    }
    fgets(localA, BUFSIZ, stdin);
    str0lastchrNUL(localA, '\n');
    while (!strlen(localA) && !sdefault)
    {
        fprintf(stdout, "%s ", question);
        fgets(localA, BUFSIZ, stdin);
        str0lastchrNUL(localA, '\n');
    }
    if (!strlen(localA))
    {
        if (size == 0)
        {
            strcpy(localA, sdefault);
        }
        else
        {
            strncpy(localA, sdefault, size);
            localA[size] = '\0';
        }
    }
    if (answer)
    {
        strcpy(answer, localA);
    }
    else
    {
        szA = strdup(localA);
    }
    return szA;
}

Int32 *i32Query( Int32 *answer, size_t size, Int32 *idefault,
                char *question )
{
    char    localA[BUFSIZ], *szl;
    Int32   *iA = answer;
    size_t  loop;

    if (!question || (size == 0)) return NULL;

    fprintf(stdout, "%s ", question);
    if (idefault)
    {
        fprintf(stdout, "[%d", idefault[0]);
        for (loop = 1; loop < size; ++loop)
        {
            fprintf(stdout, " %d", idefault[loop]);
        }
        fputs("] ", stdout);
    }
    fgets(localA, BUFSIZ, stdin);
    str0lastchrNUL(localA, '\n');
    while (!strlen(localA) && !idefault)
    {
        fprintf(stdout, "%s ", question);
        fgets(localA, BUFSIZ, stdin);
        str0lastchrNUL(localA, '\n');
    }
    if (!answer)
    {
        iA = calloc(size, sizeof(Int32));
    }
    if (!strlen(localA))
    {
        if (iA != idefault)
        {
            for (loop = 0; loop < size; ++loop)
            {
                iA[loop] = idefault[loop];
            }
        }
    }
    else
    {
        szl = strtok(localA, " ,:");
        iA[0] = atoi(szl);
        for (loop = 1; loop < size; ++loop)
        {
            if (szl) szl = strtok(NULL, " ,:");
            while (!szl)
            {
                fprintf(stdout, "\n%s (%d) ", question, (loop + 1));
                fgets(localA, BUFSIZ, stdin);
                str0lastchrNUL(localA, '\n');
                szl = strtok(localA, " ,:");
            }
            iA[loop] = atoi(szl);
        }
    }
    return iA;
}

Real32 *r32Query( Real32 *answer, size_t size, Real32 *rdefault,
                 char *question )
{
    char    localA[BUFSIZ], *szl;
    Real32  *rA = answer;
    Real64  rldefault;
    size_t  loop;

    if (!question || (size == 0)) return NULL;

    fprintf(stdout, "%s ", question);
    if (rdefault)
    {
        rldefault = (Real64) rdefault[0];
        fprintf(stdout, "[%e", rldefault);
        for (loop = 1; loop < size; ++loop)
        {
            rldefault = (Real64) rdefault[loop];
            fprintf(stdout, " %e", rldefault);
        }
        fputs("] ", stdout);
    }
    fgets(localA, BUFSIZ, stdin);
    str0lastchrNUL(localA, '\n');
    while (!strlen(localA) && !rdefault)
    {
        fprintf(stdout, "%s ", question);
        fgets(localA, BUFSIZ, stdin);
        str0lastchrNUL(localA, '\n');
    }
    if (!answer)
    {
        rA = calloc(size, sizeof(Real64));
    }
    if (!strlen(localA))
    {
        if (rA != rdefault)
        {
            for (loop = 0; loop < size; ++loop)
            {
                rA[loop] = rdefault[loop];
            }
        }
    }
    else
    {
        szl = strtok(localA, " ,:");
        rA[0] = (Real32) atof(szl);
        for (loop = 1; loop < size; ++loop)
        {
            if (szl) szl = strtok(NULL, " ,:");
            while (!szl)
            {
                fprintf(stdout, "\n%s (%d) ", question, (loop + 1));
                fgets(localA, BUFSIZ, stdin);
                str0lastchrNUL(localA, '\n');
                szl = strtok(localA, " ,:");
            }
            rA[loop] = (Real32) atof(szl);
        }
    }
    return rA;
}

Real64 *r64Query( Real64 *answer, size_t size, Real64 *rdefault,
                 char *question )
{
    char    localA[BUFSIZ], *szl;
    Real64  *rA = answer;
    size_t  loop;

    if (!question || (size == 0)) return NULL;

    fprintf(stdout, "%s ", question);
    if (rdefault)
    {
        fprintf(stdout, "[%e", rdefault[0]);
        for (loop = 1; loop < size; ++loop)
        {
            fprintf(stdout, " %e", rdefault[loop]);
        }
        fputs("] ", stdout);
    }
    fgets(localA, BUFSIZ, stdin);
    str0lastchrNUL(localA, '\n');
    while (!strlen(localA) && !rdefault)
    {
        fprintf(stdout, "%s ", question);
        fgets(localA, BUFSIZ, stdin);
        str0lastchrNUL(localA, '\n');
    }
    if (!answer)
    {
        rA = calloc(size, sizeof(Real64));
    }
    if (!strlen(localA))
    {
        if (rA != rdefault)
        {
            for (loop = 0; loop < size; ++loop)
            {
                rA[loop] = rdefault[loop];
            }
        }
    }
    else
    {
        szl = strtok(localA, " ,:");
        rA[0] = atof(szl);
        for (loop = 1; loop < size; ++loop)
        {
            if (szl) szl = strtok(NULL, " ,:");
            while (!szl)
            {
                fprintf(stdout, "\n%s (%d) ", question, (loop + 1));
                fgets(localA, BUFSIZ, stdin);
                str0lastchrNUL(localA, '\n');
                szl = strtok(localA, " ,:");
            }
            rA[loop] = atof(szl);
        }
    }
    return rA;
}


void *Query(int expected, void *answer, size_t size, 
                        void *dft, char *question) {
        char       localA[BUFSIZ];
        char       *szA = (char*) answer, *sz;
        int        iDefault = 0, iAnswer = 0;
        Int32      *i32A = (Int32*) answer, *i32;
        Real64     *r64A = (Real64*) answer, *r64;
        void       *A = answer;


        fprintf(stdout, "%s ", question);
        if (dft) {
                switch (expected) {
                case m_Int32:
                        i32 = (Int32*) dft;
                        fprintf(stdout, "[%d] ", *i32);
                        break;
                case m_Real64:
                        r64 = (Real64*) dft;
                        fprintf(stdout, "[%f] ", *r64);
                        break;
                case m_sz:
                        sz = (char*) dft;
                        if (strlen(sz))
                                fprintf(stdout, "[%s] ", sz);
                        break;
                default:
                        break;
                }
        }
        fgets(localA, BUFSIZ, stdin);
        str0lastchrNUL(localA, '\n');
        while (!strlen(localA) && !dft) {
                fprintf(stdout, "%s ", question);
                fgets(localA, BUFSIZ, stdin);
                str0lastchrNUL(localA, '\n');
        }
        if (!strlen(localA)) {
                iDefault = 1;
        }
        switch (expected) {
        case m_Int32:
                if (!answer) {
                        i32A = calloc(1, sizeof(Int32));
                        A = (void*) i32A;
                }
                if (iDefault)
                        i32A[0] = i32[0];
                else
                        i32A[0] = atoi(localA);
                break;
        case m_Real64:
                if (!answer) {
                        r64A = calloc(1, sizeof(Real64));
                        A = (void*) r64A;
                }
                if (iDefault)
                        r64A[0] = r64[0];
                else
                        r64A[0] = atof(localA);
                break;
        case m_sz:
                if (size > 0)
                        localA[size] = '\0';
                if (answer) {
                        if (iDefault)
                                strcpy(szA, sz);
                        else
                                strcpy(szA, localA);
                } else {
                        if (iDefault)
                                szA = strdup(sz);
                        else
                                szA = strdup(localA);
                        A = (void*) szA;
                }
                break;
        default:
                A = NULL;
                break;
        }
        return A;
}

