#include "chell.h"

int main(int argc, char * argv[], char **envp)
{
    int this_input = 0;
    
    char * input = (char *) malloc(sizeof(char)*128);
    strcpy (input, "noexit");
    
    char *shellname = (char *) malloc(sizeof(char)*128);
    strcpy (shellname, "myshell");
    
    printf ("[%s]%% ", shellname);
    input = getLine(input, 100);
    while (strcmp(input,"\0") == 0)
    {
        printf ("[%s]%% ", shellname);
        input = getLine(input, 100);
    }
    
    breakLine (input);
    this_input = whichInput();
    
    char ** argrv = getargrv();
    int argrc = getargrc();
    
    int loop = 1;
    
    while (this_input != -1) 
    {
        if(this_input==1) {
            cmdFromFile();
        }else if(this_input==2) {
            cmdTOFile();
        }else if(this_input==3) {
            cmdToCmd();
        }else {
            nocmd(input);
        }
        
        printf ("\n[%s]%% ", shellname);
        input = getLine(input, 100);
        while (strcmp(input,"\0") == 0)
        {
            printf ("[%s]%% ", shellname);
            input = getLine(input, 100);
        }
        breakLine (input);
        this_input = whichInput();
        argrv = getargrv();
        argrc = getargrc();
    }
    return 0;    
}