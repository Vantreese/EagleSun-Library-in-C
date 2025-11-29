/************************************************************************
                            EagleSun Library
             (c) 2000, 2001, 2002, 2014 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:
    19 Dec 2001
    01 Oct 2014

Update:
	03-Jul-2002 - round() appeared in <math.h>, causing conflict.
	To eliminate conflict, rename to esun_round().
	01-Oct-2014 Review: fEQ(0.0, y, 0.0)? How about (y == 0.0)...
	Also watching out for negative values on the return.

Note:
    In the case of very large numbers, the epsilon being larger than
    0.5, the si_round() has demonstrated more accurate rounding.

************************************************************************/

#include <math.h>
#include <esunlib.h>
/*      Truncate x to lower whole number (upper, if negative)
*/
#define _ffloor_(x)     ((float) floor((float) (x)))
#define _fceil_(x)      ((float) ceil((float) (x)))
#define _trunc_(x)      ((x) >= 0.0 ? floor(x) : ceil(x))
#define _ftrunc_(x)     ((x) >= (float) 0.0 ? _ffloor_(x) : _fceil_(x))

/*      Round x to the nearest y
        If x >= 0.0, then add 0.5 otherwise subtract 0.5, then truncate.
        Truncate meaning floor() for x >= 0.0, ceil() otherwise.

*/

double trunc( double x )
{
    return _trunc_(x);
}
float ftrunc( float x )
{
    return _ftrunc_(x);
}

double esun_round( double x, double y )
{
	double  xy;

	if (y != 0.0)
	{
		switch(fEQ(esun_Epsilon, y, 1.0))
		{
		case 1:
			x = (x >= 0.0 ? floor(x + 0.5) : ceil(x - 0.5));
			break;
		case 0:
			xy = x / y;
			x = (x >= 0.0 ? y * floor(xy + 0.5) : y * ceil(xy - 0.5));
			break;
		}
	}
	return (x >= 0.0) ?
		((x == _trunc_(x)) || (x * esun_Epsilon > 0.5) ? x : x + x * esun_Epsilon)
		: ((x == _trunc_(x)) || (x * esun_Epsilon < -0.5) ? x : x - x * esun_Epsilon);
}
float esun_fround( float x, float y )
{
	float  xy;

	if (y != 0.0)
	{
		switch(f32EQ(esun_fEpsilon, y, 1.0))
		{
		case 1:
			x = (x >= 0.0 ? _ffloor_(x + 0.5) : _fceil_(x - 0.5));
			break;
		case 0:
			xy = x / y;
			x = (x >= 0.0 ? y * _ffloor_(xy + 0.5) : y * _fceil_(xy - 0.5));
			break;
		}
	}
	return (x >= 0.0) ? ((x == _ftrunc_(x)) || (x * esun_fEpsilon > 0.5) ? x : x + x * esun_fEpsilon)
		: ((x == _ftrunc_(x)) || (x * esun_fEpsilon < -0.5) ? x : x - x * esun_fEpsilon);
}

double si_round( double x, double y)
{
	double  x1, xy, xy1;

	if (y != 0.0)
	{
		switch(fEQ(esun_Epsilon, y, 1.0))
		{
		case 1:
			x1 = 0.5 * x;
			x = (x >= 0.0 ? (fEQ(x1 * esun_Epsilon, (x1 - floor(x1)), 0.25) ? floor(x) : floor(x + 0.5))
				: (fEQ(x1 * esun_Epsilon, (x1 - ceil(x1)), -0.25) ? ceil(x) : ceil(x - 0.5)));
			break;
		case 0:
			xy = x / y;
			xy1 = 0.5 * xy;
			x = (x >= 0.0 ? (fEQ(xy1 * esun_Epsilon, (xy1 - floor(xy1)), 0.25) ? y * floor(xy) : y * floor(xy + 0.5))
				: (fEQ(xy1 * esun_Epsilon, (xy1 - ceil(xy1)), -0.25) ? y * ceil(xy) : y * ceil(xy - 0.5)));
			break;
		}
	}
	return (x >= 0.0) ? ((x == _trunc_(x)) || (x * esun_Epsilon > 0.5) ? x : x + x * esun_Epsilon)
		: ((x == _trunc_(x)) || (x * esun_Epsilon < -0.5) ? x : x - x * esun_Epsilon);
}
float fsi_round( float x, float y)
{
	float  x1, xy, xy1;

	if (y != 0.0)
	{
		switch(f32EQ(esun_fEpsilon, y, 1.0))
		{
		case 1:
			x1 = (float) 0.5 * x;
			x = (x >= 0.0 ? (f32EQ(x1 * esun_fEpsilon, (x1 - _ffloor_(x1)), 0.25) ?
				_ffloor_(x) : _ffloor_(x + 0.5)) : (f32EQ(x1 * esun_fEpsilon, (x1 - _fceil_(x1)), -0.25) ?
				_fceil_(x) : _fceil_(x - 0.5)));
			break;
		case 0:
			xy = x / y;
			xy1 = (float) 0.5 * xy;
			x = (x >= 0.0 ? (f32EQ(xy1 * esun_fEpsilon, (xy1 - _ffloor_(xy1)), 0.25) ?
			y * _ffloor_(xy) : y * _ffloor_(xy + 0.5)) : (f32EQ(xy1 * esun_fEpsilon, (xy1 - _fceil_(xy1)), -0.25) ?
			y * _fceil_(xy) : y * _fceil_(xy - 0.5)));
			break;
		}
	}
	return (x >= 0.0) ? ((x == _ftrunc_(x)) || (x * esun_fEpsilon > 0.5) ? x : x + x * esun_fEpsilon)
		: ((x == _ftrunc_(x)) || (x * esun_fEpsilon < -0.5) ? x : x - x * esun_fEpsilon);
}

int isint(double epsilon, double dd)
{
	return (fEQ(epsilon, dd, si_round(dd, 1.0)) ? 1 : 0);
}

double tryint(double epsilon, double dd)
{
	return (fEQ(epsilon, dd, si_round(dd, 1.0)) ? si_round(dd, 1.0) : dd);
}

double tryinteger(double dd)
{
	return EQ(dd, si_round(dd, 1.0)) ? si_round(dd, 1.0) : dd;
}

