/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
#include <esunlib.h>

int ChooseC(char *choices, int dft, char *question)

Date:   20 July 2000
Input:  choices: Gives available choices for users to choose from:
                choices[0] == '+' (also default) display choices,
                choices[0] == '-' do not display choices;
        dft: Default choice in the following format:
                dft == any character, the default character,
                dft == 0, blank default,
                dft == -1 do not allow default;
        question: Statement to users to get input.
Return: Choice by user.
************************************************************************/

#include <ctype.h>
#include <string.h>
#include <esunlib.h>

int ChooseC(char *choices, int dft, char *question) {
        char    C = '\377', Line[BUFSIZ], *cpchoices, *chp;
        size_t  cp, len, opt = 1;

        if ((len = strlen(choices)) == 0)
                return 0;

        if (((choices[0] == '-') || (choices[0] == '+')) && (len > 1)) {
                chp = strdup(&(choices[1]));
                --len;
                if (choices[0] == '-') {
                        opt = 0;
                } else {
                        opt = 1;
                }
        } else {
                chp = strdup(choices);
        }
        cpchoices = strdup(chp);
        for (cp = 0; cp < len; ++cp) {
                chp[cp] = tolower(chp[cp]);
                if (chp[cp] == tolower(dft))
                        cpchoices[cp] = toupper(chp[cp]);
                else
                        cpchoices[cp] = chp[cp];
        }
        while(!strchr(chp, C)) {
                if (opt)
                        fprintf(stdout, "%s [%s] ", question, cpchoices);
                else
                        fprintf(stdout, "%s ", question);
                fgets(Line, BUFSIZ, stdin);
                str0lastchrNUL(Line, '\n');
                C = tolower(Line[0]);
                if (!strlen(Line) && dft)
                        C = dft;
                if ((C == 0) && (dft == -1))
                        C = '\377';
        }
        free(cpchoices);
        free(chp);
        return (int) C;
}


/*  1 possible solution
                if (Window) {
                        wprintw(Window, "\r%s [%s] ", question, cpchoices);
                        Line[0] = wgetch(Window);
                        Line[1] = '\0';
                } else {
                        fprintf(stdout, "%s [%s] ", question, cpchoices);
                        fgets(Line, BUFSIZ, stdin);
                }
*/
