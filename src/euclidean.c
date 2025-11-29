#include <esundefs.h>

Int64 euclidean64(Int64 n, Int64 e, Int64 *mu, Int64 *d)
{
        Int64   a0, a, a1;
        Int64   q;
        Int64   x0 = 1;
        Int64   y0 = 0;
        Int64   x = 0;
        Int64   y = 1;
        Int64   x1, y1;

        a0 = (esun_abs(n) >= esun_abs(e) ? n : e);
        a = (n == a0 ? e : n);
        q = a0 / a;
        while ((a1 = a0 - a * q) != 0L)
        {
                a0 = a;
                a = a1;

                x1 = x0 - q * x;
                y1 = y0 - q * y;
                x0 = x;
                y0 = y;
                x = x1;
                y = y1;

                q = a0 / a;
        }
        *mu = (esun_abs(n) >= esun_abs(e) ? x : y);
        *d = (esun_abs(n) >= esun_abs(e) ? y : x);
        return a;
}

Int32 euclidean(Int32 n, Int32 e, Int32 *mu, Int32 *d)
{
        Int32   a0, a, a1;
        Int32   q;
        Int32   x0 = 1;
        Int32   y0 = 0;
        Int32   x = 0;
        Int32   y = 1;
        Int32   x1, y1;

        a0 = (esun_abs(n) >= esun_abs(e) ? n : e);
        a = (n == a0 ? e : n);
        q = a0 / a;
        while ((a1 = a0 - a * q) != 0L)
        {
                a0 = a;
                a = a1;

                x1 = x0 - q * x;
                y1 = y0 - q * y;
                x0 = x;
                y0 = y;
                x = x1;
                y = y1;

                q = a0 / a;
        }
        *mu = (esun_abs(n) >= esun_abs(e) ? x : y);
        *d = (esun_abs(n) >= esun_abs(e) ? y : x);
        return a;
}
