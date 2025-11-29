#ifndef _esunlib_fields_h_
#define _esunlib_fields_h_

#include <esundefs.h>

#define DBF_No_Type	0x44424600
#define DBF_Cmd_Type	0x44424601
#define DBF_FS_Type	0x44424602
#define DBF_RS_Type	0x44424603

static char _dbf_Cmd = (char) DBF_Cmd;
static char _dbf_FS = (char) DBF_FS;
static char _dbf_RS = (char) DBF_RS;

static int _idbf_Cmd = (int) DBF_Cmd;
static int _idbf_FS = (int) DBF_FS;
static int _idbf_RS = (int) DBF_RS;

#endif
