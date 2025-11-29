/************************************************************************
                            EagleSun Library
             (c) 2000, 2001, 2002, 2014 Terry Ron Vantreese
************************************************************************/
/************************************************************************
Name:   esun_sleep
Date:   23 August 2001
Update: 22 February 2002
Update: 2 October 2014
Input:  unsigned int seconds: the number of seconds to suspend process.
Action: The process will suspend for the number of seconds specified
        by seconds.
Return: int esun_sleep() = 0 if suspended for the number of seconds; or 
        if interrupted early, the number of remaining seconds.
************************************************************************/

#include <esconfig.h>

#if defined(sparc_Solaris_spro) || defined(ix86_Unix_gcc2) || defined(ix86_Win32_gcc2) || defined(sparc_Unix_gcc2)

#include <unistd.h>

int     esun_sleep(unsigned int seconds) {
        return sleep(seconds);
}

#elif defined(ix86_MSWin_msvc)

#include <Wtypes.h>
#include <winbase.h>

int esun_sleep(unsigned int seconds) {
        DWORD dwMilliSec = (DWORD) (seconds * 1000), dwMilRet;
        int iRet;

        dwMilRet = SleepEx(dwMilliSec, FALSE);
        iRet = (int) (dwMilRet / 1000);
        return iRet;
}

#else

#error Unable to compile esun_sleep() in esun_sleep.c

#endif
