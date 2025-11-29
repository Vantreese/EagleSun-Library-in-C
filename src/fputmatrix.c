#include <string.h>
#include <esunlib.h>

/*  Modes are:
    "b" for binary (outmode = 0)
    "a" for ascii-text (outmode = 1)
    "i" force 32-bit integer output (outmode = 2)
    "I" force 64-bit integer output (outmode = 3)
    "e" ascii-text in scientific notation (outmode = 4)
    4/1/2013: Tabs (\t) put too much space when a lot of space is already provided.
*/

#define mtx_BINARY      0
#define mtx_TEXT        1
#define mtx_INT32       2
#define mtx_INT64       3
#define mtx_SCI         4
#define mtx_Large	65536


int fputMatrixTryInt( char *mode, double epsilon, Matrix_t *A, FILE *Fp )
{
	if (epsilon != 0.0) mtx_TryInt(epsilon, A);
	fputMatrix(mode, A, Fp);
}

fputMatrixTryInteger( char *mode, Matrix_t *A, FILE *Fp )
{
	mtx_TryInteger(A);
	fputMatrix(mode, A, Fp);
}

int fputMatrix( char *mode, Matrix_t *A, FILE *Fp )
{
	char
		Number[80];
	int
		outmode = -1;
	Int32
		i32;
	Int64
		i64;
	size_t
		i, j;
	Real32
		r32;


	if (mode)
	{
		if (strchr(mode, 'a'))
		{
			outmode = mtx_TEXT;
		}
		if (strchr(mode, 'b'))
		{
			outmode = mtx_BINARY;
		} 
		if (strchr(mode, 'i')) 
		{ 
			outmode = mtx_INT32; 
		} 
		if (strchr(mode, 'I')) 
		{
			outmode = mtx_INT64;
		}
		if (strchr(mode, 'e'))
		{
			outmode = mtx_SCI;
		}
	}
	if (outmode == -1)
	{
		if ((Fp == stdout) || (Fp == stderr))
		{
			outmode = mtx_TEXT;
		}
		else
		{
			outmode = mtx_BINARY;
		}
	}
	if (outmode == mtx_BINARY)
	{
		if ((A->i*A->j) > mtx_Large)
		{
			fputs("mt4\n", Fp);
		}
		else
		{
			fputs("mtx\n", Fp);
		}
	}
	fprintf(Fp, "%d %d\n", A->i, A->j);
	for (i = 0; i < A->i; ++i)
	{
		for (j = 0; j < A->j; ++j)
		{
			switch (outmode)
			{
				case mtx_BINARY:
					if ((A->i*A->j) > mtx_Large)
					{
						r32 = (Real32) A->a[i][j];
						fwrite(&r32, sizeof(Real32), 1, Fp);
					}
					else
					{
						fwrite(&(A->a[i][j]), sizeof(Real64), 1, Fp);
					}
					break;
				case mtx_TEXT:
					fprintf(Fp, "  % 15.8g", A->a[i][j]);
					break;
				case mtx_INT32:
					i32 = (Int32) si_round(A->a[i][j], 1.0);
					fprintf(Fp, "  % 10d", i32);
					break;
				case mtx_INT64:
					i64 = (Int64) si_round(A->a[i][j], 1.0);
					fprintf(Fp, "  % 15s", i64toa(i64, Number, 10));
					break;
				case mtx_SCI:
					fprintf(Fp, "  % 23.16e", A->a[i][j]);
					break;
			}
		}
		if (outmode != mtx_BINARY)
		{
			fprintf(Fp, "\n");
		}
	}

	return 1;
}

