#include "chell.h"
int argrc;
char ** argrv;

void decrargrc()
{
    argrc--;
}

void nocmd (char *input)
{
    printf("%s: Command not found", input);
}

int whichInput()
{
    if(argrc == 1)
    {
       if(strcmp("exit", argrv[0])==0)
        return -1; 
    }
    else
    {
        if(strcmp("[", argrv[1]) == 0)
            return 1;
        else if(strcmp("]", argrv[1]) == 0)
            return 2;
        else if(strcmp("@", argrv[1]) == 0)
            return 3;
        else
            return 0;
    }
}

void breakLine (char * input)
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
    for (int j=1; j<argrc; j++)
    {
        tempWd=strtok(NULL, " ");
        argrv[j] = tempWd;
    }
}

char *getLine (char *input, int size)
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
{
    return argrv;
}
int getargrc()
{
    return argrc;
}

void cmdTOFile(){
    int status;
    char *tmpArg[] = {argrv[0], 0 };
    
    pid_t fork_return = fork();
    if (fork_return == 0) /* child process */ 
    {
      int bbf = open(argrv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
      if (bbf < 0)
      {
        perror("error getfile opening: ");
        exit(-1);
      }
      dup2(bbf, 1);  // make stdout go to file
      //dup2(bbf, fileno(stdin)); //reading from file to stdin
      close(bbf);
      //execl("/bin/ls",argrv[0],NULL);
      execvp(tmpArg[0], tmpArg);
      exit(0); 
    }
    else
    {
        wait(&status); 
    }
}

void cmdFromFile(){
    int status;
    char *tmpArg[] = {argrv[0], 0 };
    pid_t fork_return = fork();
    if (fork_return == 0) /* child process */ 
    {
      int bbf = open(argrv[2], O_RDONLY);
      if (bbf < 0)
      {
        perror("error getfile opening: ");
        exit(-1);
      }
      //dup2(bbf, 1);  // make stdout go to file
      dup2(bbf, fileno(stdin)); //reading from file to stdin
      close(bbf);
      //execl("/bin/ls",argrv[0],NULL);
      execvp(tmpArg[0], tmpArg);
      exit(0); 
    }
    else
    {
        wait(&status); 
    }
}

void cmdToCmd(){
    char *myargv1 [] = {argrv[0], NULL};
    char *myargv2 [] = {argrv[2], NULL};
    
    //char *myargv1 [] = {"cat", "colorfile.txt", NULL};
    //char *myargv2 [] = {"sed", "-e", "s/color/colour/g", NULL};
    
    int f_des[2];
    if(pipe(f_des) == -1)
    {
        perror("ERROR: Pipe");
        exit(1);
    }
    
    int status;    
    if (fork() == 0)
    {
        dup2(f_des[1], fileno(stdout));
        //writing std out to pipe
        close(f_des[0]);
        close(f_des[1]);
        execvp(myargv1[0], myargv1);
    } else
    {
        if (fork() == 0)
        {
            dup2(f_des[0], fileno(stdin));
            //reading from pipe to std in
            close(f_des[0]);
            close(f_des[1]);
            execvp(myargv2[0], myargv2);
        }
    }
    
    close(f_des[0]);
    close(f_des[1]);
    
    wait(&status);
    wait(&status);
}