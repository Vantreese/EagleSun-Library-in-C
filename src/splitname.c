#include <string.h>
#include <esunlib.h>

int splitname( char fullname[], char dir[], char name[], char type[] )
{
	char
		*szLine, *sz1, *sz2;
	int
		iStat = 0;

	szLine = strdup(fullname);
	sz1 = szLine;
	sz2 = str0rchrNUL(sz1, EndPathC);
	if (sz2)
	{
		if (dir)
		{
			strcpy(dir, sz1);
			if (BeginPathC)
			{
				strcatc(dir, EndPathC);
			}
			iStat |= 4;
		}
		++sz2;
		sz1 = sz2;
	}
	else
	{
		if (dir) dir[0] = '\0';
	}
	sz2 = str0rchrNUL(sz1, TypeC);
	if (name)
	{
		strcpy(name, sz1);
		iStat |= 2;
	}
	if (sz2)
	{
		++sz2;
		if (type)
		{
			strcpy(type, sz2);
			iStat |= 1;
		}
	}
	else
	{
		if (type) type[0] = '\0';
	}
	free(szLine);
	return iStat;
}
