#include <string.h>
#include <esunlib.h>

Matrix_t *fgetMatrix(void *A0, FILE *Fp)
{
	char
		szLine[BUFSIZ], *sz1, Tok[] = " ,:\t\r\n";
	int
		RawMatrix = 0;
	size_t
		i, j;
	Matrix_t
		*A = NULL;
	Real32
		af32;

	fgets(szLine, BUFSIZ, Fp);
	if (!strcmp(szLine, "mtx\n"))
	{
		RawMatrix = 1;
		fgets(szLine, BUFSIZ, Fp);
	}
	else if (!strcmp(szLine, "mt4\n"))
	{
		RawMatrix = 2;
		fgets(szLine, BUFSIZ, Fp);
	}
	sz1 = strtok(szLine, Tok);
	if (!sz1) return NULL;
	i = (size_t) atoi(sz1);
	if (i < 1)
	{
		sz1 = strtok(NULL, Tok);
		if (!sz1) return NULL;
		i = (size_t) atoi(sz1);
	}
	sz1 = strtok(NULL, Tok);
	if (!sz1) return NULL;
	j = (size_t) atoi(sz1);

	if ((i < 1) || (j < 1))
		return NULL;

	A = mtx_Create(A0, i, j);
	if (!A) return NULL;
	for (i = 0; (i < A->i) && !feof(Fp) ; ++i)
	{
		for (j = 0; (j < A->j) && !feof(Fp); ++j)
		{
			switch (RawMatrix)
			{
			case 0:
				for (sz1 = szLine; strchr(Tok, (sz1[0] = getc(Fp))) && !feof(Fp); );
				for (sz1 = &(szLine[1]); !strchr(Tok, (sz1[0] = getc(Fp))) && !feof(Fp); ++sz1);
				sz1[0] = '\0';
				A->a[i][j] = atof(szLine);
				break;
			case 1:
				fread(&(A->a[i][j]), sizeof(Real64), 1, Fp);
				break;
			case 2:
				fread(&af32, sizeof(Real32), 1, Fp);
				A->a[i][j] = (double) af32;
				break;
			}
		}
	}

	return A;
}

