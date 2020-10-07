#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define LINE 200
#define PARAM 40

void ReadCommand(char *_line, char **_parameters)
{
    int i = 0;
    char *buffer;
    char limit[] = " \n";

    fgets(_line, LINE, stdin);
    buffer = strtok(_line, limit);

    while (NULL != buffer)
    {
        _parameters[i++] = buffer;
        
        buffer = strtok(NULL, limit);
    }
    _parameters[i] = NULL;
    printf("this is the para: %s\n", _parameters[0]);
}

int main()
{

    int newPid = 0, status = -3;
    char exit[] = "exit";
    char *param[PARAM] = {0};
    char line[LINE] = {0};

    while (1)
    {
        printf(" MorShell:  ");
        ReadCommand(line, param);
        printf("this is the para:  %s\n", param[0]);
        if ((NULL != param[0]) && (strcmp(param[0], exit) == 0))
        {
            return 0;
        }

        newPid = fork();
        
        if (newPid > 0)
        {
            waitpid(-1, &status, 0);
        }
        else if (newPid < 0)
        {

            printf("Fork error\n");
            return -1;
        }
        else
        {
            execvp(param[0], param);
            printf("command not found\n");
            return -1;
        }
    }
    return 0;
}
