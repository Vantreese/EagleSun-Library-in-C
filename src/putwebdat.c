/************************************************************************
                            EagleSun Library
                      (c) 2000 Terry Ron Vantreese
                     http://eaglesun.dreamhaven.net/
*************************************************************************
*************************************************************************
#include <esunweb.h>

char *putWebDat(char *Out, char toWeb[])

Date:   30 November 2000
Input:  toWeb[]: Text to translate web data.
        *Out: predefined array to transfer translated data, or NULL.
Output: *Out: Web data, which can be sent to the web server.
Return: *Out, web data if *Out is predefined; or a pointer to a new
        array of web data, if *Out is NULL.
************************************************************************/

#include <string.h>
#include <esunlib.h>

#define AN "0123456789-._ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

char *putWebDat(char *Out, char toWeb[])
{
        char *s1;
        char cc[4];
        char *p1;
        char *szReturn;
        size_t len;


        if (!toWeb) {
                return NULL;
        }

        cc[0] = '%'; cc[3] = NUL;

        if (Out == NULL) {
                len = predictsize(Text2Web, toWeb, 1);
                s1 = calloc(len, sizeof(char));
                if (!s1) {
                        return NULL;
                }
        } else {
                Out[0] = NUL;
                s1 = Out;
        }

        p1 = toWeb;
        while (p1[0]) {
                if (p1[0] == ' ') {
                        strcatc(s1, '+');
                } else
                        if (strchr(AN, p1[0]) == NULL) {
                                char2hex(&(cc[1]), p1[0]);
                                strcat(s1, cc);
                        } else {
                                strcatc(s1, p1[0]);
                        }
                        
                        p1++;
        }
        if (!Out) {
                szReturn = strdup(s1);
                free(s1);
        } else {
                szReturn = s1;
        }
        return szReturn;
}
