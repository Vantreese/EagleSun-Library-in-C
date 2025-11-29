/************************************************************************
                            EagleSun Library
             (c) 2000, 2001, 2002, 2014 Terry Ron Vantreese
************************************************************************/
/************************************************************************
#include <esunlib.h>

int rnd32k()

Date:   4 July 2001
Update: 22 February 2002
Update:	2 October 2014 - New platform: ix86_Win32_gcc2
Input:  (void)
Action: Generate a random number in the range of [0, 32767].
Return: A random number.
************************************************************************/

#include <esconfig.h>

static int rnd_gotseed = 0;

#if defined(ix86_Unix_gcc2) || defined(ix86_Win32_gcc2) || defined(sparc_Unix_gcc2)

#include <stdlib.h>
#include <sys/time.h>

void rndseed32k(unsigned int seed) {
        srand(seed);
        rnd_gotseed = 1;
}
void rndseedtime32k() {
        struct timeval  tp;
        unsigned int    seed;

        gettimeofday(&tp, NULL);
        seed = (unsigned int) (tp.tv_sec % 4294) * tp.tv_usec;
        rndseed32k(seed);
        rnd_gotseed = 1;
}
int rnd32k(void) {
        if (!rnd_gotseed)
                rndseedtime32k();
        return ((rand() >> 16) & 0x7fff);
}

#elif defined(sparc_Solaris_spro)

#include <stdlib.h>
#include <sys/time.h>

void rndseed32k(unsigned int seed) {
        srand(seed);
        rnd_gotseed = 1;
}
void rndseedtime32k() {
        struct timeval  tp;
        unsigned int    seed;

        gettimeofday(&tp, NULL);
        seed = (unsigned int) (tp.tv_sec % 4294) * tp.tv_usec;
        rndseed32k(seed);
        rnd_gotseed = 1;
}
int rnd32k(void) {
        if (!rnd_gotseed)
                rndseedtime32k();
        return rand();
}

#elif defined(ix86_MSWin_msvc)

#include <stdlib.h>
#include <sys/timeb.h>

void rndseed32k(unsigned int seed) {
        srand(seed);
        rnd_gotseed = 1;
}
void rndseedtime32k() {
        struct timeb    tp;
        unsigned int    seed;

        ftime(&tp);
        seed = (unsigned int) (tp.time % 4294967) * tp.millitm;
        rndseed32k(seed);
        rnd_gotseed = 1;
}
int rnd32k(void) {
        if (!rnd_gotseed)
                rndseedtime32k();
        return rand();
}

#else

#error Unable to compile rnd32k() in rnd32k.c !

#endif
