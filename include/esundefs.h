/************************************************************************
                            EagleSun Library
       (c) 2000, 2001, 2002, 2003, 2011, 2014 Terry Ron Vantreese
************************************************************************/
/************************************************************************
Name:	esundefs.h
Date:	23 August 2001
Update:	22 February 2002
Update:	04-Apr-2003
Update:	31-Oct-2008
Update:	06-Oct-2011
Update:	15-Mar-2013	Epsilons more accurate for IEEE754.
Update:	01-Oct-2014	EQ(), NE(), GT(), GE(), LT(), LE() comparing
			doubles using Microsoft recommended method for
			tricky epsilon issues.
Update: 02-Oct-2014	MinGW introduces tricky path handling.

For defining types and #defines while not necessarily requiring ESUNlib.
************************************************************************/


#ifndef _esundefs_h_
#define _esundefs_h_

#define _EagleSun_Library_Version_ "EagleSun Library 2014-10-03\n"

#include <stdio.h>
#include <stdlib.h>
#include <esconfig.h>

/*      Defines */

#if defined(axp_ovms_decc) || defined(vax_ovms_decc)

#define DeviceC         ':'
#define BeginPathC      '['
#define EndPathC        ']'
#define PathC           '.'
#define PathSeparatorC  0
#define TypeC           '.'

#define CurrentPath     ""
#define ParentPath      "-"
#define TypeRequired    1

#elif defined(sparc_Solaris_spro) || defined(ix86_Unix_gcc2) || defined(sparc_Unix_gcc2)

#define DeviceC         0
#define BeginPathC      0
#define EndPathC        '/'
#define PathC           '/'
#define PathSeparatorC  ':'
#define TypeC           '.'

#define CurrentPath     "."
#define ParentPath      ".."
#define TypeRequired    0

#elif defined(ix86_Win32_gcc2)

#define DeviceC         0
#define BeginPathC      0
#define EndPathC        '\\'
#define PathC           '\\'
#define PathSeparatorC  ':'
#define TypeC           '.'

#define CurrentPath     "."
#define ParentPath      ".."
#define TypeRequired    1

#elif defined(ix86_MSWin_msvc)

#define DeviceC         ':'
#define BeginPathC      0
#define EndPathC        '\\'
#define PathC           '\\'
#define PathSeparatorC  ';'
#define TypeC           '.'

#define CurrentPath     "."
#define ParentPath      ".."
#define TypeRequired    0

#else
#error Directory symbols could not be defined in esunlib.h
#endif

#define LineSize        80
#define StrSize         1024

#define m_Int32         0x4920
#define m_Int64         0x4940
#define m_Real64        0x8840
#define m_sz            0x8900

#define NUL     '\0'
#define SP      ' '

/* Database characters */
#define DBF_Cmd '\\'
#define DBF_FS  ':'
#define DBF_RS  '\n'

#define Text2Web        0x0001
#define Web2Text        0x0100
#define Raw2DB          0x0002
#define DB2Raw          0x0200


#define esun_Epsilon    (2.220446049250313080847263336181640625e-16)
#define esun_fEpsilon   (1.1920928955078125e-07F)


#define esun_min(a, b)   ((a) < (b) ? (a) : (b))
#define esun_max(a, b)   ((a) > (b) ? (a) : (b))
#define esun_abs(x)      ((x) < 0 ? -(x) : (x))


/*  Types and Structures  */

#ifdef __cplusplus
extern "C" {
#endif 

#if defined(axp_ovms_decc) || defined(vax_ovms_decc)

typedef signed long long        Int64;
typedef unsigned long long      UInt64;

#elif defined(sparc_Solaris_spro) || defined(ix86_Unix_gcc2) || defined(sparc_Unix_gcc2)

typedef signed long long        Int64;
typedef unsigned long long      UInt64;

#elif defined(ix86_Win32_gcc2)

typedef signed long long        Int64;
typedef unsigned long long      UInt64;

#elif defined(ix86_MSWin_msvc)

typedef signed __int64          Int64;
typedef unsigned __int64        UInt64;

#else

#error Could not typedef Int64, UInt64 esunlib.h

#endif

typedef unsigned int            UInt32;
typedef unsigned short          UInt16;
typedef unsigned char           UInt8;

typedef signed int              Int32;
typedef signed short            Int16;
typedef signed char             Int8;

typedef float                   Real32;
typedef double                  Real64;


typedef enum {_false_, _true_}          esun_boolean;
typedef enum {_default_, _off_, _on_}   esun_switch;

struct dln_s
{
    struct dln_s    *prev, *next;
    void            *data;
};
typedef struct dln_s    Dln_t;

typedef struct
{
    size_t          acsize;
    unsigned char   *ac;
} rawdata_t;

typedef rawdata_t   Field_t;

typedef struct
{
    char    *LockName;
    FILE    *fp;
    int  fd;
} flFILE;

typedef struct
{
    Int32   data;
} Int32_t;

typedef struct
{
    Real64  data;
} Real64_t;

typedef struct
{
    Real64  r, i;
} Complex64_t;

typedef struct
{
    size_t  i, j;
    Real64  **a;
} Matrix_t;

typedef struct
{
    Real64  a[4][4];
} Matrix3D_t;

typedef struct
{
    size_t  n;
    Real64  *e;
} Vector_t;

typedef struct
{
    size_t  Argi;
    char    **Arg;
    char    *Path, *Name, *Type;
} Public_t;

#ifdef __cplusplus
}
#endif 

#endif
