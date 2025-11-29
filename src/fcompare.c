/************************************************************************
                            EagleSun Library
                (c) 2000, 2001, 2014 Terry Ron Vantreese
*************************************************************************
*************************************************************************

        Comparison functions for real numbers.

Date:	20 Dec 2001
Update:	01 Oct 2014
************************************************************************/
#include <stdlib.h>

static long long epsunits = 2LL;
int EQ(double a, double b)
{
	void *va = (void*) &a;
	void *vb = (void*) &b;
	long long *la = (long long*) va;
	long long *lb = (long long*) vb;
	if (a == b) return 1;
	if ((la[0] >> 63) != (lb[0] >> 63)) return 0;
	if (llabs(la[0] - lb[0]) <= epsunits) return 1;
	return 0;
}

int NE(double a, double b)
{
	return !EQ(a, b);
}

int GT(double a, double b)
{
	if (EQ(a, b) == 1) return 0;
	return (a > b ? 1 : 0);
}

int GE(double a, double b)
{
	if (EQ(a, b) == 1) return 1;
	return (GT(a, b));
}

int LT(double a, double b)
{
	if (EQ(a, b) == 1) return 0;
	return (a < b ? 1 : 0);
}

int LE(double a, double b)
{
	if (EQ(a, b) == 1) return 1;
	return (LT(a, b));
}

int fEQ( double epsilon, double a, double b )
{
    return (a == b ? 1 : ((a > (b - epsilon)) && (a < (b + epsilon)) ? 1 : 0));
}
int fGE( double epsilon, double a, double b )
{
    return (a == b ? 1 : ((a > (b - epsilon)) ? 1: 0));
}
int fGT( double epsilon, double a, double b )
{
    return (a == b ? 0 : ((a >= (b + epsilon)) ? 1: 0));
}
int fLE( double epsilon, double a, double b )
{
    return (a == b ? 1 : ((a < (b + epsilon)) ? 1: 0));
}
int fLT( double epsilon, double a, double b )
{
    return (a == b ? 0 : ((a <= (b - epsilon)) ? 1: 0));
}
int fNE( double epsilon, double a, double b )
{
    return (a == b ? 0 : ((a <= (b - epsilon)) || (a >= (b + epsilon)) ? 1 : 0));
}


int f32EQ( float epsilon, float a, float b )
{
    return (a == b ? 1 : ((a > (b - epsilon)) && (a < (b + epsilon)) ? 1 : 0));
}
int f32GE( float epsilon, float a, float b )
{
    return (a == b ? 1 : ((a > (b - epsilon)) ? 1: 0));
}
int f32GT( float epsilon, float a, float b )
{
    return (a == b ? 0 : ((a >= (b + epsilon)) ? 1: 0));
}
int f32LE( float epsilon, float a, float b )
{
    return (a == b ? 1 : ((a < (b + epsilon)) ? 1: 0));
}
int f32LT( float epsilon, float a, float b )
{
    return (a == b ? 0 : ((a <= (b - epsilon)) ? 1: 0));
}
int f32NE( float epsilon, float a, float b )
{
    return (a == b ? 0 : ((a <= (b - epsilon)) || (a >= (b + epsilon)) ? 1 : 0));
}
