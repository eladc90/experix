#include <stdio.h>
#include <string.h>     /*strtok*/
#include <sys/types.h> /*pid_t*/
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h>

#define COMMAND_SIZE 1024
#define PROCCES_FAILED -1




void ParseLine(char *_line, char **_command);




int main()
{
    char line[COMMAND_SIZE] = {0};
    char *command[COMMAND_SIZE] = {0};
    int pid =0, status = -3;
    
    while(1)
    {
        printf(" My Shell:"); 
        
        ParseLine(line, command);
        
        if (command == NULL )
        {
            return 0;
        }
        pid = fork();
        if( pid > 0)
        {
            waitpid(-1, &status, 0);
        }

        else if ( pid < 0) 
        {
            printf("process failed \n");
            return -1;
             
        }
        else
        {
            execvp(command[0], command);
            printf("process failed \n");
            return -1; 
        }   
    }
    return 0;
}


void ParseLine(char *_line, char **_command)
{
    int position = 0;
    char *buffer;

    fgets(_line , COMMAND_SIZE -1 , stdin);
    buffer = strtok(_line, " \n");
    _command[0] = buffer;
    while (NULL != buffer) 
    {
        _command[position++] = buffer;
        buffer = strtok(NULL, " \n");
    }
    _command[position] = NULL;
    printf("this is the para: %s\n", _command[0]);
}

