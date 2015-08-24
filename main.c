//  Raza Rauf
//  main.cpp
//  chell project
//
//  The program implements Unix shell commands using C.

#include "chell.h"

int main(int argc, char * argv[], char **envp)
{
    //The following two functions catch and process the interrupt and stop signals
    //AKA signals sent by the Ctrl-C and Ctrl-Z commands
    if (signal(SIGINT,signal_catcher)==SIG_ERR)
    {
        perror("Sigset cannot set SIGINT");
        exit(SIGINT);
    }
    if (signal(SIGTSTP, signal_catcher)==SIG_ERR)
    {
        perror("Sigset can not set SIGTSTP");
        exit(SIGTSTP);
    }
    
    //Declaring and initializing variables to be used later
    initHistory();
    initAlias();
    int this_input = 0;
    
    char * input = (char *) malloc(sizeof(char)*64);
    strcpy (input, "noexit");
    char *shellname = (char *) malloc(sizeof(char)*32);
    strcpy (shellname, "myshell");
    
    setShellName(shellname);
    
    printf ("[%s]%% ", shellname);
    input = getLine(input, 100);
    
    //Making sure the program does not crash if the input simply the return key
    while (strcmp(input,"\0") == 0)
    {
        printf ("[%s]%% ", shellname);
        input = getLine(input, 100);
    }
    
    setHistory(input);
    breakLine (input);
    this_input = whichInput();
    
    char ** argrv = getargrv();
    int argrc = getargrc();
    
    int loop = 1;
    
    while (loop != 0)
    {
        //Loop and process commands until the exist command is entered
        if(this_input==4) {
            if(strcmp(argrv[argrc-1], "&")==0)
            {
                //printf("Before forking PID:%d\n", getpid());
                int pid = fork();
                if(pid==0)
                {
                    //sleep(2); //putting a delay in to emphasize background process
                    //printf("\nchild PID: %d\n", getpid());
                    decrargrc();
                    list();
                    //printf("\nIn the child process - ended.\n\n");
                    return 0;
                } else
                {
                    //printf("PPID:%d\n", getpid());
                    //printf("In the parent process.\n");
                    printf("%s process running in background", argrv[0]);
                }
            } else
                list();
            
        } else if(this_input==3) {
            if(strcmp(argrv[argrc-1], "&")==0)
            {
                int pid = fork();
                if(pid==0)
                {
                    decrargrc();
                    pwd();
                    return 0;
                } else
                    printf("%s process running in background", argrv[0]);
            } else
                pwd();
        } else if(this_input==6) {
            if(strcmp(argrv[argrc-1], "&")==0)
            {
                int pid = fork();
                if(pid==0)
                {
                    decrargrc();
                    prompt();
                    shellname = getShellName();
                    return 0;
                } else
                    printf("%s process running in background", argrv[0]);
            } else
            {
                prompt();
                shellname = getShellName();
            }
        } else if(this_input==2) {
            if(strcmp(argrv[argrc-1], "&")==0)
            {
                int pid = fork();
                if(pid==0)
                {
                    decrargrc();
                    dirChange();
                    return 0;
                } else
                    printf("%s process running in background", argrv[0]);
            } else
                dirChange();
        } else if(this_input==5) {
            if(strcmp(argrv[argrc-1], "&")==0)
            {
                int pid = fork();
                if(pid==0)
                {
                    decrargrc();
                    mypid();
                    return 0;
                } else
                    printf("%s process running in background", argrv[0]);
            } else
                mypid();
        } else if(this_input==1) {
            if (getargrc() == 1)
            {
                loop = 0;
                free (input);
                free (shellname);
                
                input = NULL;
                shellname = NULL;
                
                freeDynamicMem();
                return 0;
            } else {
                printf("%s: Arguments not valid.", argrv[0]);
            }
        } else if(this_input==7) {
            if(strcmp(argrv[argrc-1], "&")==0)
            {
                int pid = fork();
                if(pid==0)
                {
                    decrargrc();
                    printHistory();
                    return 0;
                } else
                    printf("%s process running in background", argrv[0]);
            } else
                printHistory();
        } else if(this_input==8) {
            if(strcmp(argrv[argrc-1], "&")==0)
            {
                int pid = fork();
                if(pid==0)
                {
                    printf("\n***I've put a 3 second delay in to emphasize this background process\n");
                    sleep(3); //putting a delay in to emphasize background proces
                    decrargrc();
                    printEnv(envp);
                    return 0;
                } else
                    printf("%s process running in background", argrv[0]);
            } else
                printEnv(envp);
        }else if(this_input==9) {
            if(strcmp(argrv[argrc-1], "&")==0)
            {
                int pid = fork();
                if(pid==0)
                {
                    decrargrc();
                    alias();
                    return 0;
                } else
                    printf("%s process running in background", argrv[0]);
            } else
                alias();
        }else if(this_input==10) {
            if(strcmp(argrv[argrc-1], "&")==0)
            {
                int pid = fork();
                if(pid==0)
                {
                    decrargrc();
                    murder();
                    return 0;
                } else
                    printf("%s process running in background", argrv[0]);
            } else
                murder();
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
        setHistory(input);
        breakLine (input);
        this_input = whichInput();
        argrv = getargrv();
        argrc = getargrc();
    }
    return 0;
}