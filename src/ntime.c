/*

Imported from SkyRaider/CORSAIR irc channel op bots.

Input:  year: (full year), month, day, hour: (24 hour), min, sec
Return: time_t the number of seconds since 1970.
Limit:  January 1, 1970 and later.

For ntime64()
Return: Int64 the number of seconds since 1970 for positive values and
        the number of seconds before January 1, 1970 for negative values.

NEW!!!! The current usual method for time uses an equivalent type of 
Int32 or UInt32, which have a limited life of 68 years or 136 years, 
respectively.  Redefining the timing mechanism to Int64 and allowing 
for negative time for historical timing, now has a life of FIVE HUNDRED
EIGHTY-FOUR (584) BILLION years!  This is beyond necessary, however, 
this modification can go with minimal conversion, and is very useful 
for historical times.

*/

#include <esunlib.h>


#define LeapSeconds     0

static int ntime_M[12] = {0, 2678400, 5097600, 7776000, 10368000, 13046400,
        15638400, 18316800, 20995200, 23587200, 26265600, 28857600};

time_t ntime(int year, int month, int day, int hour, int min, int sec)
{
        int     ryear, rmonth, rday, rhour, rmin, rsec;
        int     lc, isl;
        int     i;
        time_t  seconds1970;


        year -= 1900;
        ryear = (year - 70) * 31536000;
        lc = ((year - 69) / 4) * 86400;
        isl = ((year % 4 == 0) && (month > 2)) ? 86400 : 0;
        i = (month - 1) % 12;
        rmonth = ntime_M[i];
        i = day - 1;
        switch (month - 1)
        {
        case 0:
                rday = i % 31;
                break;
        case 1:
                rday = ((year % 4 == 0) ? i % 29 : i % 28);
                break;
        case 2:
                rday = i % 31;
                break;
        case 3:
                rday = i % 30;
                break;
        case 4:
                rday = i % 31;
                break;
        case 5:
                rday = i % 30;
                break;
        case 6:
                rday = i % 31;
                break;
        case 7:
                rday = i % 31;
                break;
        case 8:
                rday = i % 30;
                break;
        case 9:
                rday = i % 31;
                break;
        case 10:
                rday = i % 30;
                break;
        case 11:
                rday = i % 31;
                break;
        }
        rday *= 86400;

        rhour = (hour % 24) * 3600;
        rmin = (min % 60) * 60;
        rsec = (sec % 60);

        seconds1970 = ryear + lc + rmonth + isl + rday + rhour + rmin + rsec +
                LeapSeconds;

        return seconds1970;
}


Int64 ntime64(int year, int month, int day, int hour, int min, int sec)
{
        Int64   ryear, rmonth, rday, rhour, rmin, rsec;
        Int64   lc, isl;
        int     i;
        Int64   seconds1970, i64;
	Int64   i64year = year, i64month = month;


        ryear = (i64year - 1970) * 31536000;
        lc = ((i64year - 1969) / 4) * 86400;
        isl = (((i64year % 4 == 0) && ((i64year % 100 != 0) || (i64year % 400 == 0))) && (i64month > 2)) ? 86400 : 0;
        i = (month - 1) % 12;
        rmonth = (Int64) ntime_M[i];
        i = day - 1;
	i64 = (Int64) i;
        switch (month - 1)
        {
        case 0:
                rday = i64 % 31;
                break;
        case 1:
                rday = (((i64year % 4 == 0) && ((i64year % 100 != 0) || (i64year % 400 == 0))) ? i64 % 29 : i64 % 28);
                break;
        case 2:
                rday = i64 % 31;
                break;
        case 3:
                rday = i64 % 30;
                break;
        case 4:
                rday = i64 % 31;
                break;
        case 5:
                rday = i64 % 30;
                break;
        case 6:
                rday = i64 % 31;
                break;
        case 7:
                rday = i64 % 31;
                break;
        case 8:
                rday = i64 % 30;
                break;
        case 9:
                rday = i64 % 31;
                break;
        case 10:
                rday = i64 % 30;
                break;
        case 11:
                rday = i64 % 31;
                break;
        }
        rday *= 86400;

        rhour = (hour % 24) * 3600;
        rmin = (min % 60) * 60;
        rsec = (sec % 60);

        seconds1970 = ryear + lc + rmonth + isl + rday + rhour + rmin + rsec + LeapSeconds;

        return seconds1970;
}

