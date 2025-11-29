/************************************************************************
                            EagleSun Library
             (c) 2000, 2001, 2002, 2014 Terry Ron Vantreese
************************************************************************/
/************************************************************************
Name:   esun_popen
Date:   23 August 2001
Update: 22 February 2002
Update:	2 October 2014	New platform: ix86_Win32_gcc2
Input:  char command[], char mode[]: command[] is the system action.
        mode[] is the method to call, usually set to "r" mode.
Action: Opens a pipe when executing the command sent by command[].
Return: FILE *esun_popen() = pointer to a pipe that was successfully
        opened; or NULL if unable to open a pipe.
Note:   This function was created to resolve conflicts between
        incompatible platforms.
************************************************************************/

#include <esconfig.h>

#if defined(sparc_Solaris_spro) || defined(ix86_Unix_gcc2) || defined(ix86_Win32_gcc2) || defined(sparc_Unix_gcc2)
#include <stdio.h>

FILE    *esun_popen(char command[], char mode[]) {
        return popen(command,mode);
}
#elif defined(ix86_MSWin_msvc)
#include <stdio.h>

FILE    *esun_popen(char command[], char mode[]) {
        return _popen(command, mode);
}
#else
#error Unable to compile esun_popen in esun_popen.c
#endif
