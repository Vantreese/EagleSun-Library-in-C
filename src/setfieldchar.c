#include "fields.h"


/*
 * Field characters defined by default, as defined in <esundefs.h>; as of 06-Dec-2004, they are (and have been for quite a while) defined as:
 *
 *	DBF_Cmd = '\\'  Command Character (Cmd)
 *	DBF_FS = ':'    Field Separator (FS)
 *	DBF_RS = '\n'   Record Separator (RS)
 *
 * the Unix Flatfile Database Format.
 *
 * setfieldchar() allows the programmer to change the default settings; for example, in managing a text file containing a list of passwords having a format
 * that should be converted to HTML format, separating fields with a ":" character might be difficult to manage, whereas separating fields with "\t" might be
 * easier to manage.  Web sites contain ":" and it can be difficult to represent a link with something like "http\://www.mysite.com/"; time stamps and movie
 * frames contain ":" which may be difficult to represent as "11\:23\:45\:06" -- Yuch!
 *
 * Programmer should be aware of the default settings and, if desire to change the default settings, should choose 3 unique characters to represent Cmd, FS,
 * and RS, respectively.
 */
void setfieldchar(char _Cmd, char _FS, char _RS)
{
	_dbf_Cmd = (char) _Cmd;
	_dbf_FS = (char) _FS;
	_dbf_RS = (char) _RS;

	_idbf_Cmd = (int) _Cmd;
	_idbf_FS = (int) _FS;
	_idbf_RS = (int) _RS;
}

int dbf_whattype(int cc)
{
	if (cc == _idbf_Cmd) return DBF_Cmd_Type;
	if (cc == _idbf_FS) return DBF_FS_Type;
	if (cc == _idbf_RS) return DBF_RS_Type;
	return DBF_No_Type;
}
