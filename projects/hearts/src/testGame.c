#include "game.h"

int main()
{

}

void testGameCreate()
{
    Game *game = GameCreate();
    if (game != NULL)
    {
        printf("test ok \n");
    }
    else
    {
        printf("test fail \n");
    }
    
}