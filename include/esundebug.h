/************************************************************************
                            EagleSun Library
                   (c) 2000, 2011 Terry Ron Vantreese
*************************************************************************
*************************************************************************
Name:           esundebug.h (EagleSun Debugger Tools)
Date:           4 January 2000
Update:         6 October 2011
Purpose:        Use these to help debug source code.
************************************************************************/

#ifndef _esundebug_h_
#define _esundebug_h_

#include <stdio.h>

#define debug(s)                fputs((s), stderr)
#define debugi(i)               fprintf(stderr, "%d", (i));
#define prn_debug(var, type)    fprintf(stderr, #var " = %" #type "\n", var)

#endif

