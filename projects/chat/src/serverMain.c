#include <stdio.h> /* printf */
#include "serverManager.h"

int main()
{
    ServerManager* serverMan;
    if(NULL == (serverMan = ServerManagerCreate()))
    {
        printf("Allocation failed in Server main\n");
        return 0;
    }

    ServerManagerRun(serverMan);
    ServerManagerDestroy(serverMan);
    printf("Terminating Server...\n");
    
    return 0;
}