/************************************************************************
                            EagleSun Library
             (c) 2000, 2001, 2002, 2014 Terry Ron Vantreese
************************************************************************/
/************************************************************************
Name:   esun_pclose
Date:   23 August 2001
Update: 22 February 2002
Update:	2 October 2014 - new platform: ix86_Win32_gcc2
Input:  FILE *stream: pointer to pipe file
Action: Close the pipe associated by *stream.
Return: int esun_pclose() = -1 if *stream is not associated with a pipe
        file; or if *stream was already closed.
************************************************************************/

#include <esconfig.h>

#if defined(ix86_Unix_gcc2) || defined(ix86_Win32_gcc2) || defined(sparc_Unix_gcc2) || defined(sparc_Solaris_spro)
#include <stdio.h>

int     esun_pclose(FILE *stream) {
        return pclose(stream);
}
#elif defined(ix86_MSWin_msvc)
#include <stdio.h>

int     esun_pclose(FILE *stream) {
        return _pclose(stream);
}
#else
#error Unable to compile esun_pclose in esun_pclose.c
#endif

