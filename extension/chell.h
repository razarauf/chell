#ifndef chell_h
#define chell_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define _OPEN_SYS
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#undef _OPEN_SYS

void nocmd (char *);
void breakLine (char *);
char *getLine (char *, int);
char ** getargrv();
int getargrc();
void decrargrc();
int whichInput();
void cmdTOFile();
void cmdFromFile();
void cmdToCmd();
#endif