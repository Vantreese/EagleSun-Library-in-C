/************************************************************************
                            EagleSun Library
                (c) 2000, 2001, 2002 Terry Ron Vantreese
************************************************************************/
/************************************************************************
Name:	esconfig.h
Date:	7 July 2000
Update:	27 July 2000
Update: 25 June 2001
Update: 23 August 2001
Update: 22 February 2002

The purpose of esconfig.h is to minimize the number of modifications of
the source code when porting across different systems.

Define name convention used follows the pattern
<Hardware>_<OperatingSystem>_<Compiler>
and should be used to decide which code to compile, or crash if a
platform was not properly determined.
************************************************************************/

#ifndef _EagleSun_Library_Configuration_
#define _EagleSun_Library_Configuration_

/*
#define axp_ovms_decc
#define ix86_MSWin_msvc
#define ix86_Unix_gcc2
#define sparc_Solaris_spro
#define sparc_Unix_gcc2
#define vax_ovms_decc
*/

#endif
