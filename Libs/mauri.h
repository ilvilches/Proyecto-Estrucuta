#ifndef MAURI_H_INCLUDED
#define MAURI_H_INCLUDED

void clearscr ();
void pause ();
char* readString ();
int confirm (char *);
void QError (char *);
void NumbToDay (int);
char* str_tolower (char*);
char* str_toupper (char*);
void clearstdin ();
void mgets (char*, int);


#endif // MAURI_H_INCLUDED
