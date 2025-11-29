#ifndef __ESUNWebServer_H__
#define __ESUNWebServer_H__

#include <esunlib.h>

#define Content_gif             "Content-type: image/gif\n"
#define Content_html            "Content-type: text/html\n"
#define Content_jpeg            "Content-type: image/jpeg\n"
#define Content_pbm             "Content-type: image/x-portable-bitmap\n"
#define Content_pgm             "Content-type: image/x-portable-graymap\n"
#define Content_ping            "Content-type: image/png\n"
#define Content_ppm             "Content-type: image/x-portable-pixmap\n"
#define Content_text            "Content-type: text/plain\n"
#define Content_x_bitmap        "Content-type: image/x-xbitmap\n"


#define tagBool         103
#define tagChar         105
#define tagInt          102
#define tagSwitch       104
#define tagText         101

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
        char *alink, *background, *bgcolor, *link, *text, *vlink;
} html_Body_t;


typedef struct {
        char    *href, *name;
} html_A_t;
typedef struct {
        char *action, *enctype, *method, *name, *target;
} html_Form_t;
typedef struct {
        int     t_point_size, t_size;
        char    *color, *face;
        void    *point_size, *size;
} html_Font_t;
typedef struct {
        char    *align, *clear;
} html_H_t;
typedef struct {
        char            *type;
        char            *accesskey;
        char            *name, *value;
        esun_switch     *checked;
        int             *height, *size, *width;
} html_Input_t;
typedef struct {
        char            *value;
        esun_switch     *selected;
} html_Option_t;
typedef struct {
        char    *align, *clear;
} html_P_t;
typedef struct {
        char            *align, *name;
        esun_switch     *multiple;
        int             *size;
} html_Select_t;
typedef struct {
        int     t_height, t_width;
        char    *align, *background, *bgcolor, *bordercolor;
        int     *border, *cellpadding, *cellspacing, *cols;
        void    *height, *width;
} html_Table_t;
typedef struct {
        int             t_height, t_width;
        char            *align, *background, *bgcolor, *bordercolor;
        int             *colspan, *rowspan;
        void            *height, *width;
        esun_boolean    nowrap;
} html_ThTd_t;
typedef struct {
        char            *align, *bgcolor, *bordercolor, *valign;
        esun_boolean    nowrap;
} html_Tr_t;


char *GetFormGet( char env[] );
char *GetFormPost( char env[] );
char *getWebDat(char *toText, size_t *posEq, char fromWeb[]);
char *putWebDat(char *Out, char toWeb[]);

void toWebServer( char text[] );
void tagvalueWebServer( int type, char var[], void *value );
void err404( );


void beginHtml( );
void endHtml( );
void beginHead( );
void endHead( );

void beginTitle( );
void endTitle( );


html_Body_t *initBody( html_Body_t *Body );
void beginBody( html_Body_t *Body );
void endBody( );


html_A_t *initA( html_A_t *A );
void beginA( html_A_t *A );
void endA( );

void putBr( );

html_Font_t *initFont( html_Font_t *Font );
void beginFont( html_Font_t *Font );
void endFont( );

html_Form_t *initForm( html_Form_t *Form );
void beginForm( html_Form_t *Form );
void endForm( );

html_H_t *initH( html_H_t *H );
void beginH1( html_H_t *H1 );
void endH1( );
void beginH2( html_H_t *H2 );
void endH2( );
void beginH3( html_H_t *H3 );
void endH3( );
void beginH4( html_H_t *H4 );
void endH4( );
void beginH5( html_H_t *H5 );
void endH5( );
void beginH6( html_H_t *H6 );
void endH6( );

html_Input_t *initInput( html_Input_t *Input );
void putInput( html_Input_t *Input );

html_Option_t *initOption( html_Option_t *Option );
void putOption( html_Option_t *Option, char *text );

html_P_t *initP( html_P_t *P );
void beginP( html_P_t *P );
void endP( );

html_Select_t *initSelect( html_Select_t *Select );
void beginSelect( html_Select_t *Select );
void endSelect( );

html_Table_t *initTable( html_Table_t *Table );
void beginTable( html_Table_t *Table );
void endTable( );

html_ThTd_t *initThTd( html_ThTd_t *ThTd );
void beginTd( html_ThTd_t *Td );
void endTd( );
void beginTh( html_ThTd_t *Th );
void endTh( );

html_Tr_t *initTr( html_Tr_t *Tr );
void beginTr( html_Tr_t *Tr );
void endTr( );

#ifdef __cplusplus
}
#endif

#endif
