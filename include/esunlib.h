/************************************************************************
                            EagleSun Library
          (c) 2000, 2001, 2002, 2003, 2014 Terry Ron Vantreese
************************************************************************/
/************************************************************************
Name:   esunlib.h
Date:   17 December 2001
Update: 06-Dec-2004
Update: 01-Oct-2014
Update: 03-Oct-2014
************************************************************************/

#ifndef _esunlib_h_
#define _esunlib_h_


/*      Includes        */

#include <math.h>
#include <time.h>
#include <esundefs.h>


/*      Functions       */

char            *char2hex(char hex[3], char c);

int             ChooseC(char *choices, int dft, char *question);

Int32_t         *Create_Int32_t(Int32 i32);
rawdata_t       *Create_rawdata_t( size_t acsize, unsigned char *ac );
Real64_t        *Create_Real64_t(Real64 r64);

Dln_t           *dln_Add(Dln_t *dln, Dln_t *add);
Dln_t           *dln_AddSorted(Dln_t *dln, Dln_t *add,
                               int (*ComparFn)(void *, void *));
Dln_t           *dln_Create(void *data);
void            *dln_Data(Dln_t *dln);
Dln_t           *dln_Delete(Dln_t *dln);
Dln_t           *dln_DeleteAll(Dln_t *dln);
Dln_t           *dln_Destroy(Dln_t *dln, void (*FreeData)(void *));
Dln_t           *dln_DestroyAll(Dln_t *dln, void (*FreeData)(void *));
void            *dln_GetData(Dln_t *dln, void *req, 
                             int (*GetDataFn)(void *, void *));
void            *dln_GetDataOffset(Dln_t *dln, void *req, 
                                   int (*GetOffsetFn)(void *, void *, void **));
void            *dln_GetDataSorted(Dln_t *dln, void *req, 
                                   int (*GetDataFn)(void *, void *));
Dln_t           *dln_GetNode(Dln_t *dln, void *req,
                             int (*GetFn)(void *, void *));
Dln_t           *dln_GetNodeSorted(Dln_t *dln, void *req, 
                                   int (*GetFn)(void *, void *));
Dln_t           *dln_Head(Dln_t *dln);
void            *dln_Hide(Dln_t *dln);
char            *dln_MatchSZ(Dln_t *dln, const char *req);
void            *dln_Modify(Dln_t *dln, void (*FreeData)(void *), void *data);
Dln_t           *dln_Next(Dln_t *dln);
Dln_t           *dln_Previous(Dln_t *dln);
void            *dln_ReData(Dln_t *dln, void *data);
Dln_t           *dln_ReNext(Dln_t *dln, Dln_t *next);
Dln_t           *dln_RePrevious(Dln_t *dln, Dln_t *prev);
Dln_t           *dln_Sort( Dln_t *dln, int (*ComparFn)(void *, void *) );
Dln_t           *dln_Tail(Dln_t *dln);

FILE            *esun_popen(char command[], char mode[]);
int             esun_pclose(FILE *stream);
int             esun_sleep(unsigned int seconds);
int             esun_strncasecmp(char s1[], char s2[], size_t len) ;

Int64           euclidean64(Int64 n, Int64 e, Int64 *mu, Int64 *d);
Int32           euclidean(Int32 n, Int32 e, Int32 *mu, Int32 *d);

int             EQ(double a, double b);
int             NE(double a, double b);
int             GT(double a, double b);
int             GE(double a, double b);
int             LT(double a, double b);
int             LE(double a, double b);

int             fEQ( double epsilon, double a, double b );
int             fGE( double epsilon, double a, double b );
int             fGT( double epsilon, double a, double b );
int             fLE( double epsilon, double a, double b );
int             fLT( double epsilon, double a, double b );
int             fNE( double epsilon, double a, double b );

int             f32EQ( float epsilon, float a, float b );
int             f32GE( float epsilon, float a, float b );
int             f32GT( float epsilon, float a, float b );
int             f32LE( float epsilon, float a, float b );
int             f32LT( float epsilon, float a, float b );
int             f32NE( float epsilon, float a, float b );

int             fgetBE(FILE *Fp) ;
Field_t         *fgetField( int *iStat, FILE *fp );
int             fgetLE(FILE *Fp) ;
Matrix_t        *fgetMatrix(void *A0, FILE *Fp);
Dln_t           *fgetss(Dln_t *dln, FILE *fp) ;

int             flclose(flFILE *flp);
flFILE          *flopen(const char *path, const char *mode, int duration, int reserved);

int             fputBE(int c, FILE *Fp) ;
void            fputField( Field_t *Field, FILE *fp );
void            fputFields( Field_t **Fields, size_t NumFields, FILE *fp );
int             fputLE(int c, FILE *Fp) ;
int             fputMatrix( char *mode, Matrix_t *A, FILE *Fp );
int             fputMatrixTryInt( char *mode, double epsilon, Matrix_t *A, FILE *Fp );
int             fputMatrixTryInteger( char *mode, Matrix_t *A, FILE *Fp );
Dln_t           *fgetsec( Dln_t *dln, size_t secsize, FILE *fp );
size_t          fputsec( Dln_t *dln, FILE *fp );
int             fputss(Dln_t *dln, FILE *fp) ;

float           esun_fround( float x, float y );
float           fsi_round( float x, float y);

char            *fullname( char fname[], char path[], char name[], char type[] );

char            hex2char(char hex[2]);

char            *i64toa( Int64 value, char *string, int radix );
char            *i64toa_crj( Int64 value, char *string, int radix, int len );

int             isint(double epsilon, double dd);

int             lockfile(char *lockfilename, char *mode, unsigned int timeout);

int             Logger( time_t *Epoch, char *envp[] );

int             mem2cmp(const void *b1, size_t len1, 
                        const void *b2, size_t len2);
void            *memac(const void *b, size_t lenb, 
                       const void *ac, size_t lenac);

Matrix_t        *mtx_Add( Matrix_t *C0, Matrix_t *A, Matrix_t *B );
Matrix_t        *mtx_Create( Matrix_t *A, size_t i, size_t j );
Dln_t           *mtx_Decode( Matrix_t *M );
Matrix_t        *mtx_Encode( int rndpad, Dln_t *dln );
Real64          mtx_Far( Matrix_t *A );
Real64          mtx_HI( Matrix_t *A );
Matrix_t        *mtx_I( Matrix_t *A, size_t n );
Matrix_t        *mtx_Inverse( Matrix_t *A1, Matrix_t *A, Real64 *Det );
Real64          mtx_LO( Matrix_t *A );
Matrix_t        *mtx_Multiply( Matrix_t *C0, Matrix_t *A, Matrix_t *B );
Matrix_t        *mtx_O( Matrix_t *A, size_t i, size_t j );
void            mtx_Range( Matrix_t *A, Real64 *lo, Real64 *hi );
Matrix_t        *mtx_Subtract( Matrix_t *C0, Matrix_t *A, Matrix_t *B );
Matrix_t        *mtx_TryInt( Real64 epsilon, Matrix_t *A );
void            mtx_Unlink( Matrix_t *A, Real64 **aa, size_t m );
size_t		mtx_Width( Matrix_t *A );
size_t		mtx_Height( Matrix_t *A );
void		mtx_In(Matrix_t *A, int i, int j, double v);
Real64		mtx_Out(Matrix_t *A, int i, int j);

time_t          ntime(int year, int month, int day, int hour, int min, int sec);
Int64           ntime64(int year, int month, int day, int hour, int min, int sec);

size_t          predictsize( int trans, void *vv, size_t vsize );

int             ptrtoint(void *v) ;

void            *Query(int expected, void *answer, size_t size,
                       void *dft, char *question);
char            *szQuery( char *answer, size_t size, char *sdefault,
                         char *question );
Int32           *i32Query( Int32 *answer, size_t size, Int32 *idefault,
                          char *question );
Real32          *r32Query( Real32 *answer, size_t size, Real32 *rdefault,
                          char *question );
Real64          *r64Query( Real64 *answer, size_t size, Real64 *rdefault,
                          char *question );

int             rnd32k(void);
void            rndseed32k(unsigned int seed);
void            rndseedtime32k();

double          esun_round( double x, double y );

void            SetAllEnv(int argc, char *argv[]) ;

double          si_round( double x, double y);

int             splitname( char fullname[], char dir[], char name[], char type[] );
void            setfieldchar(char _Cmd, char _FS, char _RS);

char            *str0catc( char str[], int c ) ;
char            *str0chrNUL( char str[], int c ) ;
char            *str0dup( char str[] ) ;
char            *str0dupz( char str[] ) ;
char            *str0lastchr( char str[], int c ) ;
char            *str0lastchrNUL( char str[], int c ) ;
char            *str0rchrNUL( char str[], int c ) ;
char            *strcatc( char str[], int c );
char            *strchrNUL( char str[], int c ) ;
char            *strlastchr( char str[], int c ) ;
char            *strlastchrNUL( char str[], int c );

Int32           Struct2Int32( void *data );
Real64          Struct2Real64( void *data );

double          tryint(double epsilon, double dd);
double          tryinteger(double dd);

double          trunc( double x );

int             ulockfile(int lockfd);

char            *utoa( unsigned int value, char *string, int radix );
char            *utoa_c0f( unsigned int value, char *string, int radix, 
                          int len );
char            *utoa_crj( unsigned int value, char *string, int radix, 
                          int len );

#endif

