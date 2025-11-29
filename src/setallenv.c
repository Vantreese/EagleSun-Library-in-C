/************************************************************************
                            EagleSun Library
                (c) 2000, 2001, 2002 Terry Ron Vantreese
************************************************************************/
/************************************************************************
    #include <esunlib.h>

    void SetAllEnv(int argc, char *argv[])

Date:   23 August 2001
Update: 02 February 2002
Input:  argc, *argv[], *env[]: Entry variables from main().
Action: ARG variables are made globally available via the 
        Public_t Public structure; and the complete path name of the
        program made globally available.
        Public.Argi = (size_t) argc;
        Public.Arg = argv;
        Public.Path = (the directory path of the program);
        Public.Name = (the name of the program);
        Public.Type = (the type of the program, usually .EXE in Dos or
                Windows, not available in UNIX);
************************************************************************/

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <esunlib.h>

Public_t        Public = {0, NULL, NULL, NULL, NULL};

void SetAllEnv(int argc, char *argv[])
{
    char    *szLine, *sz1, *sz2, Tok[2] = {PathSeparatorC, '\0'};
    char    szFilePath[BUFSIZ];
#if defined(sparc_Solaris_spro) || defined(ix86_Unix_gcc2) || defined(ix86_Win32_gcc2) || defined(sparc_Unix_gcc2)
    struct  stat statbuf;
#elif defined(ix86_MSWin_msvc)
    struct  _stat statbuf;
#else
#error  //  Cannot get structure for stat()
#endif

    Public.Argi = (size_t) argc;
    Public.Arg = argv;
    
    szLine = strdup(Public.Arg[0]);
    sz1 = szLine;
    sz2 = str0rchrNUL(sz1, EndPathC);
    if(sz2)
    {
        if (BeginPathC)
        {
            Public.Path = calloc((strlen(sz1) + 2), sizeof(char));
            strcpy(Public.Path, sz1);
            strcatc(Public.Path, EndPathC);
        }
        else
        {
            Public.Path = strdup(sz1);
        }
        ++sz2;
        sz1 = sz2;
    }
    else
    {
        Public.Path = NULL;
    }
    sz2 = str0rchrNUL(sz1, TypeC);
    Public.Name = strdup(sz1);
    if(sz2)
    {
        ++sz2;
        Public.Type = strdup(sz2);
    }
    else
    {
#if defined(axp_ovms_decc) || defined(vax_ovms_decc) || defined(ix86_MSWin_msvc)
        /* Don't rely on TypeRequired */
        Public.Type = strdup("EXE");
#else
        Public.Type = NULL;
#endif
    }
    free(szLine);

    if (PathSeparatorC)
    {
        if (!Public.Path)
        {
            sz1 = strdup(CurrentPath);
            strcpy(szFilePath, sz1);
            strcatc(szFilePath, EndPathC);
            strcat(szFilePath, Public.Name);
            if (Public.Type)
            {
                strcatc(szFilePath, TypeC);
                strcat(szFilePath, Public.Type);
            }
#if defined(sparc_Solaris_spro) || defined(ix86_Unix_gcc2) || defined(ix86_Win32_gcc2) || defined(sparc_Unix_gcc2)
            if (!stat(szFilePath, &statbuf))
            {
                Public.Path = strdup(sz1);
            }
#elif defined(ix86_MSWin_msvc)
            if (!_stat(szFilePath, &statbuf))
            {
                Public.Path = strdup(sz1);
            }
#endif
            free(sz1);
        }
        if (!Public.Path)
        {
            sz1 = getenv("PATH");
            if(sz1)
            {
                szLine = strdup(sz1);
                sz1 = strtok(szLine, Tok);
                while(sz1)
                {
                    strcpy(szFilePath, sz1);
                    strcatc(szFilePath, EndPathC);
                    strcat(szFilePath, Public.Name);
                    if (Public.Type)
                    {
                        strcatc(szFilePath, TypeC);
                        strcat(szFilePath, Public.Type);
                    }
#if defined(sparc_Solaris_spro) || defined(ix86_Unix_gcc2) || defined(ix86_Win32_gcc2) || defined(sparc_Unix_gcc2)
                    if (!stat(szFilePath, &statbuf))
                    {
                        Public.Path = strdup(sz1);
                    }
#elif defined(ix86_MSWin_msvc)
                    if (!_stat(szFilePath, &statbuf))
                    {
                        Public.Path = strdup(sz1);
                    }
#endif
                    if(!Public.Path)
                    {
                        sz1 = strtok(NULL, Tok);
                    }
                    else
                    {
                        sz1 = NULL;
                    }
                }
                free(szLine);
            }
        }
    }
    if (!Public.Path)
    {
        Public.Path = strdup(CurrentPath);
    }
}
