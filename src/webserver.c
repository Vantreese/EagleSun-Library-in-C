#include "esunweb.h"

void toWebServer( char text[] )
{
        if (text)
                fputs(text, stdout);
}
void tagvalueWebServer( int type, char var[], void *value )
{
        char            *sz, *c;
        int             *i;
        esun_switch     *sw;
        int             iStat;

        if (!var)
                return;
        fprintf(stdout, " %s", var);
        if (value) {
                switch (type) {
                case tagChar:
                        c = value;
                        iStat = fprintf(stdout, "=\"%c\"", *c);
                        break;
                case tagInt:
                        i = value;
                        iStat = fprintf(stdout, "=%d", *i);
                        break;
                case tagSwitch:
                        sw = value;
                        if (*sw == _off_)
                                iStat = fputs("=\"OFF\"", stdout);
                        if (*sw == _on_)
                                fputs("=\"ON\"", stdout);
                        break;
                case tagText:
                        sz = value;
                        iStat = fprintf(stdout, "=\"%s\"", sz);
                        break;
                default:
                        break;
                }
        }
}


void err404( ) {
        char    *Document, *Referer, *ServerUrl;


        Document = getenv("DOCUMENT_URI");
        Referer = getenv("HTTP_REFERER");
        ServerUrl = getenv("SERVER_URL");

        toWebServer("<title>Sorry. I cannot find this resource</title>\n");
        toWebServer("<body bgcolor='#ffffff' text='#000000' alink='#ff0000' vlink='#00007f' link='#0000ff'>\n");
        toWebServer("<h2 align=center><img border=0  src=\"/internal-roxen-roxen\" alt=\"File not found\">\n");
        toWebServer("<p><hr noshade>\n");
        toWebServer("<i>Sorry</i></h2>\n");
        toWebServer("<br clear>\n");
        toWebServer("<font size=\"+2\">The resource requested <i>");
        if (Document)
                toWebServer(Document);
        toWebServer("</i>\n");
        toWebServer("cannot be found.<p>\n");
        toWebServer("\n");
        toWebServer("If you feel that this is a configuration error, please contact the administrators or the author of the\n");
        if (Referer) {
                toWebServer("<a href=\"");
                toWebServer(Referer);
                toWebServer("\">referring</a>\n\n");
        } else {
                toWebServer("\nreferring\n");
        }
        toWebServer("page.<p>\n");
        toWebServer("</font>\n");
        toWebServer("<hr noshade>Roxen Challenger/1.3.122");
        if (ServerUrl) {
                toWebServer(", at <a href=\"");
                toWebServer(ServerUrl);
                toWebServer("\">");
                toWebServer(ServerUrl);
                toWebServer("</a>.\n");
        } else {
                toWebServer(".\n");
        }
        toWebServer("</body>\n");
}

/*****************************************************************************/

void beginHtml( )
{
        toWebServer("<html>\n");
}
void endHtml( )
{
        toWebServer("</html>\n");
}


void beginHead( )
{
        toWebServer("<head>\n");
}
void endHead( )
{
        toWebServer("</head>\n\n");
}


void beginTitle( )
{
        toWebServer("<title>");
}
void endTitle( )
{
        toWebServer("</title>\n");
}


html_Body_t *initBody( html_Body_t *Body )
{
        if (!Body) {
                Body = calloc(1, sizeof(html_Body_t));
                return Body;
        }
        Body->alink = NULL;
        Body->background = NULL;
        Body->bgcolor = NULL;
        Body->link = NULL;
        Body->text = NULL;
        Body->vlink = NULL;
        return Body;
}
void beginBody( html_Body_t *Body )
{
        if (!Body) {
                toWebServer("<body>\n");
                return;
        }
        toWebServer("<body");
        if (Body->alink) {
                tagvalueWebServer(tagText, "alink", Body->alink);
        }
        if (Body->background) {
                tagvalueWebServer(tagText, "background", Body->background);
        }
        if (Body->bgcolor) {
                tagvalueWebServer(tagText, "bgcolor", Body->bgcolor);
        }
        if (Body->link) {
                tagvalueWebServer(tagText, "link", Body->link);
        }
        if (Body->text) {
                tagvalueWebServer(tagText, "text", Body->text);
        }
        if (Body->vlink) {
                tagvalueWebServer(tagText, "vlink", Body->vlink);
        }
        toWebServer(">\n");
}
void endBody( )
{
        toWebServer("</body>\n");
}


html_A_t *initA( html_A_t *A )
{
        if (!A) {
                A = calloc(1, sizeof(html_A_t));
                return A;
        }
        A->href = NULL;
        A->name = NULL;
        return A;
}
void beginA( html_A_t *A )
{
        toWebServer("<a");
        if (A->href)
                tagvalueWebServer(tagText, "href", A->href);
        if (A->name)
                tagvalueWebServer(tagText, "name", A->name);
        toWebServer(">");
}
void endA( )
{
        toWebServer("</a>");
}


void putBr( )
{
        toWebServer("<br>\n");
}


html_Font_t *initFont( html_Font_t *Font )
{
        if (!Font) {
                Font = calloc(1, sizeof(html_Font_t));
                return Font;
        }
        Font->color = NULL;
        Font->face = NULL;
        Font->point_size = NULL;
        Font->size = NULL;
        Font->t_point_size = 0;
        Font->t_size = 0;
        return Font;
}
void beginFont( html_Font_t *Font )
{       /*  Assume at least 1 member is valid.  */
        toWebServer("<font");
        if (Font->color)
                tagvalueWebServer(tagText, "color", Font->color);
        if (Font->face)
                tagvalueWebServer(tagText, "face", Font->face);
        if (Font->point_size)
                tagvalueWebServer(Font->t_point_size, "point-size",
                        Font->point_size);
        if (Font->size)
                tagvalueWebServer(Font->t_size, "size", Font->size);
        toWebServer(">");
}
void endFont( )
{
        toWebServer("</font>");
}


html_Form_t *initForm( html_Form_t *Form )
{
        if (!Form) {
                Form = calloc(1, sizeof(html_Form_t));
                return Form;
        }
        Form->action = NULL;
        Form->enctype = NULL;
        Form->method = NULL;
        Form->name = NULL;
        Form->target = NULL;
        return Form;
}
void beginForm( html_Form_t *Form )
{       /*  Allow to crash if not properly defined.  */
        toWebServer("<form");
        tagvalueWebServer(tagText, "action", Form->action);
        if (Form->enctype)
                tagvalueWebServer(tagText, "enctype", Form->enctype);
        if (Form->method)
                tagvalueWebServer(tagText, "method", Form->method);
        if (Form->name)
                tagvalueWebServer(tagText, "name", Form->name);
        if (Form->target)
                tagvalueWebServer(tagText, "target", Form->target);
        toWebServer(">\n");
}
void endForm( )
{
        toWebServer("</form>\n");
}


html_H_t *initH( html_H_t *H )
{
        if (!H) {
                H = calloc(1, sizeof(html_H_t));
                return H;
        }
        H->align = NULL;
        H->clear = NULL;
        return H;
}
void beginH1( html_H_t *H1 )
{
        if (!H1) {
                toWebServer("<h1>");
                return;
        }
        toWebServer("<h1");
        if (H1->align)
                tagvalueWebServer(tagText, "align", H1->align);
        if (H1->clear)
                tagvalueWebServer(tagText, "clear", H1->clear);
        toWebServer(">");
}
void endH1( )
{
        toWebServer("</h1>\n");
}


void beginH2( html_H_t *H2 )
{
        if (!H2) {
                toWebServer("<h2>");
                return;
        }
        toWebServer("<h2");
        if (H2->align)
                tagvalueWebServer(tagText, "align", H2->align);
        if (H2->clear)
                tagvalueWebServer(tagText, "clear", H2->clear);
        toWebServer(">");
}
void endH2( )
{
        toWebServer("</h2>\n");
}


void beginH3( html_H_t *H3 )
{
        if (!H3) {
                toWebServer("<h3>");
                return;
        }
        toWebServer("<h3");
        if (H3->align)
                tagvalueWebServer(tagText, "align", H3->align);
        if (H3->clear)
                tagvalueWebServer(tagText, "clear", H3->clear);
        toWebServer(">");
}
void endH3( )
{
        toWebServer("</h3>\n");
}


void beginH4( html_H_t *H4 )
{
        if (!H4) {
                toWebServer("<h4>");
                return;
        }
        toWebServer("<h4");
        if (H4->align)
                tagvalueWebServer(tagText, "align", H4->align);
        if (H4->clear)
                tagvalueWebServer(tagText, "clear", H4->clear);
        toWebServer(">");
}
void endH4( )
{
        toWebServer("</h4>\n");
}


void beginH5( html_H_t *H5 )
{
        if (!H5) {
                toWebServer("<h5>");
                return;
        }
        toWebServer("<h5");
        if (H5->align)
                tagvalueWebServer(tagText, "align", H5->align);
        if (H5->clear)
                tagvalueWebServer(tagText, "clear", H5->clear);
        toWebServer(">");
}
void endH5( )
{
        toWebServer("</h5>\n");
}


void beginH6( html_H_t *H6 )
{
        if (!H6) {
                toWebServer("<h6>");
                return;
        }
        toWebServer("<h6");
        if (H6->align)
                tagvalueWebServer(tagText, "align", H6->align);
        if (H6->clear)
                tagvalueWebServer(tagText, "clear", H6->clear);
        toWebServer(">");
}
void endH6( )
{
        toWebServer("</h6>\n");
}


html_Input_t *initInput( html_Input_t *Input )
{
        if (!Input) {
                Input = calloc(1, sizeof(html_Input_t));
                return Input;
        }
        Input->accesskey = NULL;
        Input->checked = NULL;
        Input->height = NULL;
        Input->name = NULL;
        Input->size = NULL;
        Input->type = NULL;
        Input->value = NULL;
        Input->width = NULL;
        return Input;
}
void putInput( html_Input_t *Input )
{       /*  Allow to crash if not properly defined.  */
        toWebServer("<input");

        tagvalueWebServer(tagText, "type", Input->type);

        if (Input->accesskey)
                tagvalueWebServer(tagChar, "accesskey", Input->accesskey);
        if (Input->checked)
                tagvalueWebServer(tagSwitch, "checked", Input->checked);
        if (Input->height)
                tagvalueWebServer(tagInt, "height", Input->height);
        if (Input->name)
                tagvalueWebServer(tagText, "name", Input->name);
        if (Input->size)
                tagvalueWebServer(tagInt, "size", Input->size);
        if (Input->value)
                tagvalueWebServer(tagText, "value", Input->value);
        if (Input->width)
                tagvalueWebServer(tagInt, "width", Input->width);

        toWebServer(">");
}


html_Option_t *initOption( html_Option_t *Option )
{
        if (!Option) {
                Option = calloc(1, sizeof(html_Option_t));
                return Option;
        }
        Option->selected = NULL;
        Option->value = NULL;
        return Option;
}
void putOption( html_Option_t *Option, char *text )
{
        if (!text) {
                return;
        }
        if (!Option) {
                toWebServer("<option>");
                toWebServer(text);
                toWebServer("\n");
                return;
        }
        toWebServer("<option");
        if (Option->selected)
                tagvalueWebServer(tagSwitch, "selected", Option->selected);
        if (Option->value)
                tagvalueWebServer(tagText, "value", Option->value);
        toWebServer(">");
        toWebServer(text);
        toWebServer("\n");
}


html_P_t *initP( html_P_t *P )
{
        if (!P) {
                P = calloc(1, sizeof(html_P_t));
                return P;
        }
        P->align = NULL;
        P->clear = NULL;
        return P;
}
void beginP( html_P_t *P )
{
        if (!P) {
                toWebServer("<p>");
                return;
        }
        toWebServer("<p");
        if (P->align)
                tagvalueWebServer(tagText, "align", P->align);
        if (P->clear)
                tagvalueWebServer(tagText, "clear", P->clear);
        toWebServer(">");
}
void endP( )
{
        toWebServer("</p>\n");
}


html_Select_t *initSelect( html_Select_t *Select )
{
        if (!Select) {
                Select = calloc(1, sizeof(html_Select_t));
                return Select;
        }
        Select->align = NULL;
        Select->multiple = NULL;
        Select->name = NULL;
        Select->size = NULL;
        return Select;
}
void beginSelect( html_Select_t *Select )
{
        toWebServer("<select");
        tagvalueWebServer(tagText, "name", Select->name);
        if (Select->align)
                tagvalueWebServer(tagText, "align", Select->align);
        if (Select->size)
                tagvalueWebServer(tagInt, "size", Select->size);
        if (Select->multiple)
                tagvalueWebServer(tagSwitch, "multiple", Select->multiple);
        toWebServer(">\n");
}
void endSelect( )
{
        toWebServer("</select>\n");
}


html_Table_t *initTable( html_Table_t *Table )
{
        if (!Table) {
                Table = calloc(1, sizeof(html_Table_t));
                return Table;
        }
        Table->align = NULL;
        Table->background = NULL;
        Table->bgcolor = NULL;
        Table->border = NULL;
        Table->bordercolor = NULL;
        Table->cellpadding = NULL;
        Table->cellspacing = NULL;
        Table->cols = NULL;
        Table->height = NULL;
        Table->t_height = 0;
        Table->t_width = 0;
        Table->width = NULL;
        return Table;
}
void beginTable( html_Table_t *Table )
{
        if (!Table) {
                toWebServer("<table>\n");
                return;
        }
        toWebServer("<table");
        if (Table->align)
                tagvalueWebServer(tagText, "align", Table->align);
        if (Table->background)
                tagvalueWebServer(tagText, "background", Table->background);
        if (Table->bgcolor)
                tagvalueWebServer(tagText, "bgcolor", Table->bgcolor);
        if (Table->bordercolor)
                tagvalueWebServer(tagText, "bordercolor", Table->bordercolor);
        if (Table->border)
                tagvalueWebServer(tagInt, "border", Table->border);
        if (Table->cellpadding)
                tagvalueWebServer(tagInt, "cellpading", Table->cellpadding);
        if (Table->cellspacing)
                tagvalueWebServer(tagInt, "cellspacing", Table->cellspacing);
        if (Table->cols)
                tagvalueWebServer(tagInt, "cols", Table->cols);
        if (Table->height)
                tagvalueWebServer(Table->t_height, "height", Table->height);
        if (Table->width)
                tagvalueWebServer(Table->t_width, "width", Table->width);
        toWebServer(">\n");
}
void endTable( )
{
        toWebServer("</table>\n");
}


html_ThTd_t *initThTd( html_ThTd_t *ThTd )
{
        if (!ThTd) {
                ThTd = calloc(1, sizeof(html_ThTd_t));
                return ThTd;
        }
        ThTd->align = NULL;
        ThTd->background = NULL;
        ThTd->bgcolor = NULL;
        ThTd->bordercolor = NULL;
        ThTd->colspan = NULL;
        ThTd->height = NULL;
        ThTd->nowrap = _false_;
        ThTd->rowspan = NULL;
        ThTd->t_height = 0;
        ThTd->t_width = 0;
        ThTd->width = NULL;
        return ThTd;
}
void beginTd( html_ThTd_t *Td )
{
        if (!Td) {
                toWebServer("<td>");
                return;
        }
        toWebServer("<td");
        if (Td->align)
                tagvalueWebServer(tagText, "align", Td->align);
        if (Td->background)
                tagvalueWebServer(tagText, "background", Td->background);
        if (Td->bgcolor)
                tagvalueWebServer(tagText, "bgcolor", Td->bgcolor);
        if (Td->bordercolor)
                tagvalueWebServer(tagText, "bordercolor", Td->bordercolor);
        if (Td->colspan)
                tagvalueWebServer(tagInt, "colspan", Td->colspan);
        if (Td->height)
                tagvalueWebServer(Td->t_height, "height", Td->height);
        if (Td->nowrap)
                toWebServer(" nowrap");
        if (Td->rowspan)
                tagvalueWebServer(tagInt, "rowspan", Td->rowspan);
        if (Td->width)
                tagvalueWebServer(Td->t_width, "width", Td->width);
        toWebServer(">");
}
void endTd( )
{
        toWebServer("</td>\n");
}


void beginTh( html_ThTd_t *Th )
{
        if (!Th) {
                toWebServer("<th>");
                return;
        }
        toWebServer("<th");
        if (Th->align)
                tagvalueWebServer(tagText, "align", Th->align);
        if (Th->background)
                tagvalueWebServer(tagText, "background", Th->background);
        if (Th->bgcolor)
                tagvalueWebServer(tagText, "bgcolor", Th->bgcolor);
        if (Th->bordercolor)
                tagvalueWebServer(tagText, "bordercolor", Th->bordercolor);
        if (Th->colspan)
                tagvalueWebServer(tagInt, "colspan", Th->colspan);
        if (Th->height)
                tagvalueWebServer(Th->t_height, "height", Th->height);
        if (Th->nowrap)
                toWebServer(" nowrap");
        if (Th->rowspan)
                tagvalueWebServer(tagInt, "rowspan", Th->rowspan);
        if (Th->width)
                tagvalueWebServer(Th->t_width, "width", Th->width);
        toWebServer(">");
}
void endTh( )
{
        toWebServer("</th>\n");
}


html_Tr_t *initTr( html_Tr_t *Tr )
{
        if (!Tr) {
                Tr = calloc(1, sizeof(html_Tr_t));
                return Tr;
        }
        Tr->align = NULL;
        Tr->bgcolor = NULL;
        Tr->bordercolor = NULL;
        Tr->nowrap = _false_;
        Tr->valign = NULL;
        return Tr;
}
void beginTr( html_Tr_t *Tr )
{
        if (!Tr) {
                toWebServer("<tr>\n");
                return;
        }
        toWebServer("<tr");
        if (Tr->align)
                tagvalueWebServer(tagText, "align", Tr->align);
        if (Tr->bgcolor)
                tagvalueWebServer(tagText, "bgcolor", Tr->bgcolor);
        if (Tr->bordercolor)
                tagvalueWebServer(tagText, "bordercolor", Tr->bordercolor);
        if (Tr->nowrap)
                toWebServer(" nowrap");
        if (Tr->valign)
                tagvalueWebServer(tagText, "valign", Tr->valign);
        toWebServer(">\n");
}
void endTr( )
{
        toWebServer("</tr>\n");
}

