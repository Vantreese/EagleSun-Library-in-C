#include <esunlib.h>

Matrix_t *mtx_Add( Matrix_t *C0, Matrix_t *A, Matrix_t *B )
{
	Matrix_t *C = NULL;
	size_t i, j;

	if((A->i != B->i) || (A->j != B->j))    return NULL;

	C = (Matrix_t*) mtx_Create(C0, A->i, B->j);
	if(!C)  return NULL;
	for(i = 0; i < A->i; ++i)
	{
		for(j = 0; j < B->j; ++j)
		{
			C->a[i][j] = A->a[i][j] + B->a[i][j];
		}
	}

	return C;
}

#define mtx_RandomDevice "/dev/random"

Int64 mtx_int15random(void)
{
	FILE *rnddev;
	Int64 rnd15;

	rnddev = fopen(mtx_RandomDevice, "rb");
	if (!rnddev) return 0L;
	fread(&rnd15, sizeof(Int64), 1, rnddev);
	fclose(rnddev);
	return (rnd15&0x7fff);
	/*
	 * rnd15 = (Int64) rnd32k();
	 *
	 */
}

/*      Purpose: to encode 8-bit data into a Matrix format, and
	to decode (if possible) a Matrix into 8-bit data.
	dln->data is of type rawdata_t*.
*/

#define BaseRndPad      6
#define BaseRndShift    9
#define RndMask	 0xfffe00
#define ActiveMask      0x100L

Matrix_t *mtx_Encode( int rndpad, Dln_t *dln )
{
	Dln_t *dln1;
	int sr = 0, sl = 0;
	Matrix_t *M;
	rawdata_t *rr;
	size_t i, j;
	Int64 cc = 0L;

	dln1 = dln;
	rr = dln_Data(dln1);
	j = rr->acsize;
	for (i = 0; dln1; ++i)
		dln1 = dln_Next(dln1);
	M = mtx_Create(NULL, i, j);
	if (!M)
		return NULL;
	if (rndpad > (BaseRndPad + BaseRndShift))
	{
		rndpad = BaseRndPad + BaseRndShift;
	}
	if (rndpad > BaseRndPad)
		sl = rndpad - BaseRndPad;
	if (rndpad < BaseRndPad)
		sr = BaseRndPad - rndpad;
	for (i = 0; i < M->i; ++i)
	{
		rr = dln_Data(dln);
		for (j = 0; j < M->j; ++j)
		{
			if (rndpad > 0)
			{
				cc = (Int64) rnd32k();
				if (sl)
				{
					cc = cc << sl;
				}
				if (sr)
				{
					cc = cc >> sr;
				}
			}
			else
			{
				cc = 0L;
				rndpad = 0;
			}
			cc &= RndMask;
			if (i == (M->i - 1))
			{
				cc |= (j >= rr->acsize ? (rnd32k() % 256) : rr->ac[j] | ActiveMask);
			}
			else
			{
				cc |= rr->ac[j] | ActiveMask;
			}
			M->a[i][j] = (Real64) cc;
		}
		dln = dln_Next(dln);
	}
	return M;
}


Dln_t *mtx_Decode( Matrix_t *M )
{
	Dln_t *dln = NULL, *dln1;
	Int64 cc;
	rawdata_t *raw;
	size_t i, j, size;
	unsigned char *ac;

	for (i = 0; i < M->i; ++i)
	{
		ac = calloc(M->j, sizeof(unsigned char));
		size = 0;
		for (j = 0; j < M->j; ++j)
		{
			cc = (Int64) si_round(M->a[i][j], 1.0);
			if ((cc & ActiveMask) == ActiveMask)
			{
				ac[j] = (unsigned char) (0xff & cc);
				++size;
			}
			else
			{
				ac[j] = '\0';
			}
		}
		if (size > 0)
		{
			raw = Create_rawdata_t(size, ac);
			dln1 = dln_Create(raw);
			dln = dln_Add(dln, dln1);
		}
	}
	return dln;
}



/*  Correct invalid dimensions of a matrix  */
#define _mtx_correctdim_(i, j) { \
	i = (i < 1 ? 1 : i); \
	j = (j < 1 ? 1 : j); \
}
/*  */

Matrix_t *mtx_Create( Matrix_t *A, size_t i, size_t j )
{
	size_t m;
	int mkA = 0;

	_mtx_correctdim_(i, j);

	if(!A)
	{
		A = calloc(1, sizeof(Matrix_t));
		mkA = 1;
	}
	if(!A)
	{
		return NULL;
	}
	if(!A->a)
	{
		A->i = i;
		A->j = j;
		A->a = (Real64**) malloc(i * sizeof(Real64*));
		if(!A->a)
		{
			if(mkA)
			{
				mtx_Unlink(A, NULL, 0);
			}
			return NULL;
		}
		for(m = 0; m < i; ++m)
		{
			A->a[m] = (Real64*) malloc(j * sizeof(Real64));
			if(!A->a[m])
			{
				i = m;
				if(mkA)
				{
					mtx_Unlink(A, A->a, m);
				}
				else
				{
					mtx_Unlink(NULL, A->a, m);
				}
				return NULL;
			}
		}
	}
	else
	{
		if((A->i != i) || (A->j != j))
		{
			return NULL;
		}
	}

	return A;
}

/*
 * Find the element farthest away from 0
 *
 */
Real64 mtx_Far( Matrix_t *A )
{
	Real64 far, mag;
	size_t loopi, loopj;

	far = fabs(A->a[0][0]);
	for (loopi = 0; loopi < A->i; ++loopi)
	{
		for (loopj = 0; loopj < A->j; ++loopj)
		{
			mag = fabs(A->a[loopi][loopj]);
			far = (mag > far ? mag : far);
		}
	}
	return far;
}


Real64 mtx_HI( Matrix_t *A )
{
	Real64
		hi;
	size_t
		loopi, loopj;

	hi = A->a[0][0];
	for (loopi = 0; loopi < A->i; ++loopi)
	{
		for (loopj = 0; loopj < A->j; ++loopj)
		{
			hi = (A->a[loopi][loopj] > hi ? A->a[loopi][loopj] : hi);
		}
	}
	return hi;
}


Matrix_t *mtx_I( Matrix_t *A, size_t n )
{
	Matrix_t *I;
	size_t si, sj;

	I = (Matrix_t*) mtx_Create(A, n, n);
	if (!I) return NULL;
	for (si = 0; si < n; ++si)
	{
		for (sj = 0; sj < n; ++sj)
		{
			I->a[si][sj] = (si == sj ? 1.0 : 0.0);
		}
	}

	return I;
}

/*
 *
 * I don't know how to set the epsilon value. However, previously
 * I used this...
 *
 *   epsilon = esun_Epsilon * 2.0 * n
 *
 * I think n should be a value furthest away from 0.
 *
 * Microsoft advises this is too tricky to handle. There's a bit-wise
 * method available to use.
 *
 */

/* #define _mtx_debug_ */

Matrix_t *mtx_Inverse_small( Matrix_t *A1, Matrix_t *A, Real64 *Det );

Matrix_t *mtx_Inverse( Matrix_t *A1, Matrix_t *A, Real64 *Det )
{
	size_t n, i, j, k;
	Real64 xtest = 0.0;
	Matrix_t *C = NULL, *II = NULL;

	if (A->i != A->j)
		return NULL;
	n = A->i;
	if (n <= 4)
	{
		C = mtx_Inverse_small(A1, A, Det);
		return C;
	}
	II = mtx_Create(NULL, n, n);
	if (!II)
	{
		if (Det)
			*Det = 0.0;
		return NULL;
	}
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			II->a[i][j] = tryinteger(A->a[i][j]);
		}
	}
	C = mtx_I(A1, n);
	if (!C)
	{
		if (Det)
			*Det = 0.0;
		return NULL;
	}
	if (Det)
		*Det = 1.0;
	for (i = 0; i < n; ++i)
	{
		if (EQ(II->a[i][i], 0.0))
		{
			for (k = i + 1; ((k < n) && EQ(II->a[k][i], 0.0)); ++k);
			if (k < n)
			{
				for (j = 0; j < n; ++j)
				{
					II->a[i][j] += II->a[k][j];
					C->a[i][j] += C->a[k][j];
				}
			}
			else
			{
				if (A1)
				{
					mtx_Unlink(C, C->a, C->i);
				}
				mtx_Unlink(II, II->a, II->i);
				if (Det)	*Det = 0.0;
				return NULL;
			}
#ifdef _mtx_debug_
fprintf(stderr, "\tadd row %d to row %d:", k, i);
for (j = 0; j < n; ++j)
{
fprintf(stderr, "\t% .6f", II->a[i][j]);
}
for (j = 0; j < n; ++j)
{
fprintf(stderr, "\t% .6f", C->a[i][j]);
}
fputs("\n", stderr);
#endif
		}
		xtest = II->a[i][i];
#ifdef _mtx_debug_
fprintf(stderr, "xtest = % .6f", xtest);
#endif
		if (Det)
			*Det *= xtest;
		if (NE(xtest, 1.0))
		{
			for (j = 0; j < n; ++j)
			{
				II->a[i][j] /= xtest;
				C->a[i][j] /= xtest;
			}
		}
#ifdef _mtx_debug_
fprintf(stderr, "\tnormalize row %d:", i);
for (j = 0; j < n; ++j)
{
fprintf(stderr, "\t% .6f", II->a[i][j]);
}
for (j = 0; j < n; ++j)
{
fprintf(stderr, "\t% .6f", C->a[i][j]);
}
fputs("\n", stderr);
#endif
		for (k = 0; k < n; ++k)
		{
			if (k != i)
			{
				xtest = II->a[k][i];
#ifdef _mtx_debug_
fprintf(stderr, "xtest = % .6f", xtest);
#endif
				if (EQ(xtest, 1.0))
				{
					for (j = 0; j < n; ++j)
					{
						II->a[k][j] -= II->a[i][j];
						C->a[k][j] -= C->a[i][j];
					}
				}
				else
				{
					for (j = 0; j < n; ++j)
					{
						II->a[k][j] -= xtest * II->a[i][j];
						C->a[k][j] -= xtest * C->a[i][j];
					}
				}
#ifdef _mtx_debug_
fprintf(stderr, "\tadd row %d to row %d:", i, k);
for (j = 0; j < n; ++j)
{
fprintf(stderr, "\t% .6f", II->a[k][j]);
}
for (j = 0; j < n; ++j)
{
fprintf(stderr, "\t% .6f", C->a[k][j]);
}
fputs("\n", stderr);
#endif
			}
		}
	}
	mtx_Unlink(II, II->a, II->i);

	return C;
}

/*      This method is extremely slow when calculating 9x9 or larger.
 *      Therefore, it should be used on matrices of 4x4 or smaller.
 */
Real64 mtx_Determinant_small(Matrix_t *A, int rowI[], int colJ[])
{
	Real64 Det = 0.0, el;
	size_t n, i = 0, j = 0, loopi, loopj;

	if (A->i != A->j) return 0.0;
	n = A->i;
	loopi = 0;
	while ((loopi < n) && !rowI[loopi])
	{
		++loopi;
	}
	if (loopi < n)
	{
		if (rowI[loopi])
		{
			j = 0;
			for (loopj = 0; loopj < n; ++loopj)
			{
				if (colJ[loopj])
				{
					rowI[loopi] = 0;
					colJ[loopj] = 0;
					el = ((i+j)%2 == 0 ? A->a[loopi][loopj] : -A->a[loopi][loopj]);
					Det += el*mtx_Determinant_small(A, rowI, colJ);
					rowI[loopi] = 1;
					colJ[loopj] = 1;
					++j;
				}
			}
			++i;
		}
	}

	return ((i+j) == 0 ? 1.0 : tryinteger(Det));
}

Matrix_t *mtx_Inverse_small( Matrix_t *A1, Matrix_t *A, Real64 *Det )
{
	int *rowI, *colJ;
	Matrix_t *C = NULL;
	size_t n, i, j;
	Real64 lDet;

	if (A->i != A->j) return NULL;
	n = A->i;
	rowI = calloc(n, sizeof(int));
	colJ = calloc(n, sizeof(int));
	for (i = 0; i < n; ++i)
	{
		rowI[i] = colJ[i] = 1;
	}
	C = mtx_Create(A1, n, n);
	/* lDet = mtx_Determinant_small(A, NULL, NULL); This line was used in the past. */
	lDet = mtx_Determinant_small(A, rowI, colJ);
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			rowI[i] = 0;
			colJ[j] = 0;
			C->a[j][i] = ((i+j)%2 == 0 ? 1.0 : -1.0)*mtx_Determinant_small(A, rowI, colJ)/lDet;
			rowI[i] = 1;
			colJ[j] = 1;
		}
	}
	free(rowI);
	free(colJ);
	if (Det) *Det = lDet;
	return C;
}


void mtx_In(Matrix_t *A, int i, int j, double v)
{
	A->a[i-1][j-1] = v;
}
Real64 mtx_Out(Matrix_t *A, int i, int j)
{
	return (A->a[i-1][j-1]);
}



Real64 mtx_LO( Matrix_t *A )
{
	Real64 lo;
	size_t loopi, loopj;

	lo = A->a[0][0];
	for (loopi = 0; loopi < A->i; ++loopi)
	{
		for (loopj = 0; loopj < A->j; ++loopj)
		{
			lo = (A->a[loopi][loopj] < lo ? A->a[loopi][loopj] : lo);
		}
	}
	return lo;
}


Matrix_t *mtx_Multiply( Matrix_t *C0, Matrix_t *A, Matrix_t *B )
{
	Matrix_t *C = NULL;
	Real64 x;
	size_t i, j, k;

	if (A->j != B->i) return NULL;

	C = (Matrix_t*) mtx_Create(C0, A->i, B->j);
	if (!C) return NULL;
	for(k = 0; k < A->i; ++k)
	{
		for(j = 0; j < B->j; ++j)
		{
			x = 0.0;
			for(i = 0; i < A->j; ++i)
			{
				x += A->a[k][i] * B->a[i][j];
			}
			C->a[k][j] = x;
		}
	}

	return C;
}



Matrix_t *mtx_O( Matrix_t *A, size_t i, size_t j )
{
	Matrix_t *O;
	size_t ni, nj;

	O = (Matrix_t*) mtx_Create(A, i, j);
	if (!O) return NULL;
	for (ni = 0; ni < i; ++ni)
	{
		for (nj = 0; nj < j; ++nj)
		{
			O->a[ni][nj] = 0.0;
		}
	}

	return O;
}


void mtx_Range( Matrix_t *A, Real64 *lo, Real64 *hi )
{
	size_t loopi, loopj;

	*lo = *hi = A->a[0][0];
	for (loopi = 0; loopi < A->i; ++loopi)
	{
		for (loopj = 0; loopj < A->j; ++loopj)
		{
			*lo = (A->a[loopi][loopj] < *lo ? A->a[loopi][loopj] : *lo);
			*hi = (A->a[loopi][loopj] > *hi ? A->a[loopi][loopj] : *hi);
		}
	}
}


Matrix_t *mtx_Subtract( Matrix_t *C0, Matrix_t *A, Matrix_t *B )
{
	Matrix_t *C = NULL;
	size_t i, j;

	if((A->i != B->i) || (A->j != B->j))    return NULL;

	C = (Matrix_t*) mtx_Create(C0, A->i, B->j);
	if(!C)  return NULL;
	for(i = 0; i < A->i; ++i)
	{
		for(j = 0; j < B->j; ++j)
		{
			C->a[i][j] = A->a[i][j] - B->a[i][j];
		}
	}

	return C;
}


Matrix_t *mtx_TryInt( Real64 epsilon, Matrix_t *A )
{
	size_t loopi, loopj;

	for (loopi = 0; loopi < A->i; ++loopi)
	{
		for (loopj = 0; loopj < A->j; ++loopj)
		{
			A->a[loopi][loopj] = tryint(epsilon, A->a[loopi][loopj]);
		}
	}
	return A;
}


Matrix_t *mtx_TryInteger( Matrix_t *A )
{
	size_t loopi, loopj;

	for (loopi = 0; loopi < A->i; ++loopi)
	{
		for (loopj = 0; loopj < A->j; ++loopj)
		{
			A->a[loopi][loopj] = tryinteger(A->a[loopi][loopj]);
		}
	}
	return A;
}


void mtx_Unlink( Matrix_t *A, Real64 **aa, size_t m )
{
	size_t i;

	if(aa)
	{
		for(i = 0; i < m; ++i)
		{
			free(aa[i]);
		}
	}
	if(A)   free(A);
}

size_t mtx_Width( Matrix_t *A )
{
	if (!A) return 0;
	return A->j;
}
size_t mtx_Height( Matrix_t *A )
{
	if (!A) return 0;
	return A->i;
}
