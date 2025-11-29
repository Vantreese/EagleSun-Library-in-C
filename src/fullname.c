/************************************************************************
                            EagleSun Library
                   (c) 2000-2002 Terry Ron Vantreese
*************************************************************************
*************************************************************************

Date:   8 December 2000
Update: 23-Apr-2002
Input:  path[], name[], type[]
Output: fname[]
Action: Get full name of file.  No defaults.
Return: fname[], or newly allocated array if fname[] is NULL.
************************************************************************/

#include <string.h>
#include <esunlib.h>

char *fullname( char fname[], char path[], char name[], char type[] )
{
	char
		*ret;
	char
		*szPath = NULL, *szName = NULL, *szType = NULL;
	size_t
		l1 = 0;

	if (path)
	{
		if (path[0])
		{
			szPath = path;
			l1 += strlen(szPath);
			if (!BeginPathC)
			{
				++l1;
			}
		}
	}

	if (name)
	{
		szName = name;
		l1 += strlen(szName);
	}

	if (type)
	{
		szType = type;
		l1 += 1 + strlen(szType);
	}

	if (fname)
		ret = fname;
	else
		ret = calloc((l1 + 1), sizeof(char));

	ret[0] = '\0';
	if (szPath)
	{
		strcat(ret, szPath);
		if (!BeginPathC)
		{
			strcatc(ret, EndPathC);
		}
	}
	if (szName)
	{
		strcat(ret, szName);
	}
	if (szType)
	{
		strcatc(ret, TypeC);
		strcat(ret, szType);
	}
	return ret;
}
