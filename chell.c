#include "chell.h"

//Declaring variables
int argrc;
char ** argrv;
char * shell_name;
char ** shell_history;
int history_counter;
int history_limit;

char ** alias_table = (char**)malloc(10);

char *alias_exit = (char *) malloc(sizeof(char)*128);
char *alias_cd = (char *) malloc(sizeof(char)*128);
char *alias_pwd = (char *) malloc(sizeof(char)*128);
char *alias_list = (char *) malloc(sizeof(char)*128);
char *alias_pid = (char *) malloc(sizeof(char)*128);
char *alias_prompt = (char *) malloc(sizeof(char)*128);
char *alias_history = (char *) malloc(sizeof(char)*128);
char *alias_printenv = (char *) malloc(sizeof(char)*128);
char *alias_alias = (char *) malloc(sizeof(char)*128);
char *alias_murder = (char *) malloc(sizeof(char)*128);

void decrargrc()
//Function decrements the argument counter
{
    argrc--;
}

void printEnv(char **envrp)
{
//Function prints the enironment
    
    if(argrc == 1)
    {
        int i=0;
        while(*(envrp+i) != NULL)
        {
            printf("%s\n", envrp[i]);
            i++;
        }
    } else if (argrc == 2)
    {
        char * tmpPtr = getenv (argrv[1]);
        if(tmpPtr != NULL)
            printf("%s", tmpPtr);
        else
            printf("Invalid environment variable.");
    } else
    {
        printf("%s: Arguments not valid.", argrv[0]);
    }
    
}

void initAlias()
//Function initializes commands with default aliases
{
    strcpy(alias_exit, "exit");
    strcpy(alias_cd, "cd");
    strcpy(alias_pwd, "pwd");
    strcpy(alias_list, "list");
    strcpy(alias_pid, "pid");
    strcpy(alias_prompt, "prompt");
    strcpy(alias_history, "history");
    strcpy(alias_printenv, "printenv");
    strcpy(alias_alias, "alias");
    strcpy(alias_murder, "kill");
}

int whichInput()
//Function compares the user input and returns the appropriate integer
{
    if(strcmp(alias_exit, argrv[0]) == 0)
        return 1;
    else if(strcmp(alias_cd, argrv[0]) == 0)
        return 2;
    else if(strcmp(alias_pwd, argrv[0]) == 0)
        return 3;
    else if(strcmp(alias_list, argrv[0]) == 0)
        return 4;
    else if(strcmp(alias_pid, argrv[0]) == 0)
        return 5;
    else if(strcmp(alias_prompt, argrv[0]) == 0)
        return 6;
    else if(strcmp(alias_history, argrv[0]) == 0)
        return 7;
    else if(strcmp(alias_printenv, argrv[0]) == 0)
        return 8;
    else if(strcmp(alias_alias, argrv[0]) == 0)
        return 9;
    else if(strcmp(alias_murder, argrv[0]) == 0)
        return 10;
    else
        return -1;
}

void alias()
//Function changes the default command alias to a user defined alias
{
    if(argrc == 1)
    {
        printf("%s\n", alias_exit);
        printf("%s\n", alias_cd);
        printf("%s\n", alias_pwd);
        printf("%s\n", alias_list);
        printf("%s\n", alias_pid);
        printf("%s\n", alias_prompt);
        printf("%s\n", alias_history);
        printf("%s", alias_printenv);
        
    } else if (argrc == 3)
    {
        if(strcmp(argrv[1], alias_exit) == 0)
            strcpy(alias_exit, argrv[2]);
        else if (strcmp(argrv[1], alias_cd) == 0)
            strcpy(alias_cd, argrv[2]);
        else if (strcmp(argrv[1], alias_pwd) == 0)
            strcpy(alias_pwd, argrv[2]);
        else if (strcmp(argrv[1], alias_list) == 0)
            strcpy(alias_list, argrv[2]);
        else if (strcmp(argrv[1], alias_pid) == 0)
            strcpy(alias_pid, argrv[2]);
        else if (strcmp(argrv[1], alias_prompt) == 0)
            strcpy(alias_prompt, argrv[2]);
        else if (strcmp(argrv[1], alias_history) == 0)
            strcpy(alias_history, argrv[2]);
        else if (strcmp(argrv[1], alias_murder) == 0)
            strcpy(alias_murder, argrv[2]);
        else
            printf("%s: Command not valid for alias.", argrv[1]);
    } else
    {
        printf("%s: Arguments not valid.", argrv[0]);
    }
}

void murder()
//Functions sends the kill command to the process with the specified PID
{
    if(argrc == 2)
    {
        //int status;
        //if(fork()==0)
        //{
            int pid = atoi (argrv[1]);
            if(kill(pid, SIGKILL) < 0)
                printf("kill failed");
            //exit(0);    
        //}
        //else{wait(&status);}
        
    }else if (argrc == 3)
    {
        //if(fork()==0)
        //{
            char *tmp2 = argrv[1];
            //printf("tmp2: %s\n",tmp2+1);
            int pid_signal = atoi (tmp2+1);
            //printf("signal: %i ",pid_signal);
            int pid = atoi (argrv[2]);
            //printf("pid: %i ",pid);
            if(kill(pid, pid_signal) < 0)
                printf("kill failed");
            //exit(0);    
        //}
    }else
    {
        printf("%s: Arguments not valid.", argrv[0]);
    }
    
}

void initHistory()
//Function intializes the command history
{
    history_counter = 0;
    history_limit = 5;
    shell_history = (char**)malloc(sizeof(char**)*128);
}

void setHistory(char *input)
//Function sets the command history
{
    char * tempStr = (char *) malloc(sizeof(char)*128);
    strcpy(tempStr, input);
    shell_history[history_counter] = tempStr;
    history_counter++;
}

void printHistory()
//Function prints the command history
{
    int tmp_history_limit = 0;
    if(history_counter<history_limit)
    {
        tmp_history_limit = history_counter;
    } else
    {
        tmp_history_limit = history_limit;    
    }
    
    if(argrc == 1)
    {
        int counter = 0;
        int counter_down = history_counter;
        while(counter < tmp_history_limit)
        //while(counter_down != 0)
        {
            counter_down--;
            printf("%s\n", shell_history[counter_down]);
            counter++;
        }
    } else if (argrc == 2)
    {
        history_limit = atoi(argrv[1]);
        if(history_counter<history_limit)
        {
            tmp_history_limit = history_counter;
        } else
        {
            tmp_history_limit = history_limit;    
        }
        int counter = 0;
        int counter_down = history_counter;
        while(counter < tmp_history_limit)
        //while(counter_down != 0)
        {
            counter_down--;
            printf("%s\n", shell_history[counter_down]);
            counter++;
        }
    } else
    {
        printf("%s: Arguments not valid.", argrv[0]);
    }
    
}
void list ()
//Function lists the directories and files in the current folder
{
    int fork_true = 0;
    int pid;
    
    // if(strcmp(argrv[argrc-1], "&")==0){
    if(argrc == 1)
    {
        DIR *dir;
        struct dirent *file_entry;
        dir = opendir(".");
        if(dir == NULL)
        {
            printf("Error -- list");
        } else
        {
           while ((file_entry = readdir(dir)) != NULL)
           {
              if((strcmp(file_entry->d_name, ".") != 0) && (strcmp(file_entry->d_name, "..") != 0))
                printf("%s\n", file_entry->d_name); 
           }
           closedir(dir);
        }
    } else if (argrc > 1)
    {
        DIR *dir;
        struct dirent *file_entry;
        for (int k=1; k<argrc; k++)
        {
            dir = opendir(argrv[k]);
            if(dir == NULL)
            {
                printf("Error -- list");
            } else
            {
                printf("\n%s:\n",argrv[k]);
                while ((file_entry = readdir(dir)) != NULL)
                {
                   if((strcmp(file_entry->d_name, ".") != 0) && (strcmp(file_entry->d_name, "..") != 0))
                      printf("%s\n", file_entry->d_name); 
                }
                closedir(dir);
            }    
        }
    }
    else
    {
        printf("%s: Arguments not valid.", argrv[0]);
    }

}

void pwd ()
//Function lists the path to the current directory
{
    if(argrc == 1)
    {
        char pwd[2048];
        char *check_pwd = getcwd(pwd, sizeof(pwd));
        if (check_pwd == NULL)
            printf("Error -- PWD"); 
        else
            printf("%s", pwd);
    } else
    {
        printf("%s: Arguments not valid.", argrv[0]);
    }
}

void prompt ()
//Sets the shell name to the name specified by user
{
    if(argrc == 1)
    {
        printf ("> input prompt prefix: ");
        scanf("%s", shell_name);
    } else if (argrc == 2) {
        strcpy (shell_name, argrv[1]);
    } else {
        printf("%s: Arguments not valid.", argrv[0]);
    }   
}

void nocmd (char *input)
{
    printf("%s: Command not found", input);
}

void breakLine (char * input)
//Function breaks the user input line into arguments to process later
{
    //break the argument into individual words and count how many arguments
    char * tempStr = (char *) malloc(sizeof(char)*128);
    strcpy (tempStr, input);
    argrc = 0;
    char * tempWd = strtok(tempStr, " ");
    argrc++;    
    while((tempWd=strtok(NULL, " "))!=NULL)
    {
        argrc++;
    }
    
    argrv = (char**)malloc(argrc+1);
    strcpy (tempStr, input);
    
    tempWd = strtok(tempStr, " ");
    //storing the tempWd in words array to print later
    argrv[0] = tempWd;
    //cout << words[0];
    for (int j=1; j<argrc; j++)
    {
        tempWd=strtok(NULL, " ");
        argrv[j] = tempWd;
        //cout << words[j];
    }
    
    //printf("%i\n", argrc);
    //for (int j=0; j<argrc; j++){
    //    printf("%s", argrv[j]);
    //}   
}

char *getLine (char *input, int size)
//Function reads user input and processes for use later
{
    //remove the \n at the end of the input if it exists
    char *tempPtr = fgets(input, size, stdin);
    
    if (tempPtr != NULL)
    {
        int last_char = strlen (input) - 1;
        
        if (tempPtr[last_char] == '\n')
            tempPtr[last_char] = '\0';
    }
    return tempPtr;
}

char ** getargrv()
//Returns the pointer to user arguments entered
{
    return argrv;
}

int getargrc()
//Returns the number of arguments entered
{
    return argrc;
}

void setShellName(char *in_shell_name)
//Sets the shell name to the specified name
{
    shell_name = (char *) malloc(sizeof(char)*128);
    strcpy (shell_name, in_shell_name);
}

char *getShellName()
//Returns a pointer to the current shell name
{
    return shell_name;
}

void mypid()
//Returns the PID of the current process
{
    if(argrc == 1)
    {
        printf("PID : %d", getpid());  
    } else {
        printf("%s: Arguments not valid.", argrv[0]);
    }  
}

void dirChange()
//Changes the current directory to a valid directory specified by the user
{
    if(argrc == 1)
    {
        int check_change = chdir(getenv("HOME"));
        if (check_change == 0)
        {
            printf ("Directory changed to Home directory.");
        } else
        {
            printf ("Error changing to HOME directory. Error #: %i", check_change);
        }
    }
    else if(argrc == 2)
    {
        int check_change = chdir(argrv[1]);
        if (check_change == 0)
        {
            printf ("Directory changed to %s directory.", argrv[1]);
        } else
        {
            printf ("Error changing to %s directory. Error #: %i", argrv[1], check_change);
        }    
    }
    else
    {
        printf("%s: Arguments not valid.", argrv[0]);
    }
}

void signal_catcher(int the_sig)
{
        //The following line is commented out, but may be necessary in
        //some implementations. Otherwise, the signal may return to its
        //default action after one occurance of the signal is handled
        //signal(the_sig, signal_catcher); //reset
        if (the_sig == SIGTSTP)
            printf("\nCtrl-Z\n");
        else if (the_sig == SIGINT)
            printf("\nCtrl-C\n");
        if (the_sig == SIGQUIT)
                exit(1);
}
