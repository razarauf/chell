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
#include <signal.h>
#include <sys/wait.h>
#undef _OPEN_SYS

void list ();
void pwd ();
void prompt ();
void nocmd (char *);
void breakLine (char *);
char *getLine (char *, int);
char ** getargrv();
int  getargrc();
void decrargrc();
void setShellName(char *);
char *getShellName();
void mypid();
void dirChange();
void printHistory();
void initHistory();
void setHistory(char *);
void initAlias();
int  whichInput();
void alias();
void printEnv(char **);
void murder();
void signal_catcher(int);
void freeDynamicMem();
#endif