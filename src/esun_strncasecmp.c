/************************************************************************
                            EagleSun Library
             (c) 2000, 2001, 2002, 2014 Terry Ron Vantreese
************************************************************************/
/************************************************************************
Name:   esun_strncasecmp
Date:   23 August 2001
Update: 22 February 2002
Update: 2 October 2014 - New platform: ix86_Win32_gcc2
Input:  char s1[], char s2[], size_t len
Action: Lexicographically compare s1[] tp s2[] with case-insensitive
        comparison, up to len characters, or up to nul-terminator if
        len == 0.
Return: int esun_strncasecmp() = 0 if s1[] matches to s2[]; > 0 if s1[]
        is lexicographically greater than s2[]; < 0 if s1[] is
        lexicographically less than s2[].
************************************************************************/

#include <string.h>
#include <esconfig.h>

#if defined(sparc_Solaris_spro) || defined(ix86_Unix_gcc2) || defined(ix86_Win32_gcc2) || defined(sparc_Unix_gcc2)
int     esun_strncasecmp(char s1[], char s2[], size_t len) {
        return(len == 0 ? strcasecmp(s1, s2) : strncasecmp(s1, s2, len));
}
#elif defined(ix86_MSWin_msvc)
int     esun_strncasecmp(char s1[], char s2[], size_t len) {
        return(len == 0 ? stricmp(s1, s2) : strnicmp(s1, s2, len));
}
#else
#error Unable to compile esun_strncasecmp in esun_strncasecmp.c
#endif

