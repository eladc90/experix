#include <stdio.h>
#include "game.h"
#include "hand.h"
#include "Deck.h"
#include "ADTErr.h"
#include "vector.h"
#include "heap.h"
#include "player.h"
#include <string.h>
void testDeckCreate();
void testGameCreate();
void testPlayerCreate();
int main()
{
    /* testPlayerCreate();
    testDeckCreate();
    testGameCreate(); */
	Game *game;
	game = GameCreate();
	GamePlay(game);
	GameDestroy();
	return 0;
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

void testPlayerCreate()
{
    int test;
    char *name = "heff";
    char *check;
    Player *player;
    player = PlayerCreate(name, 0);
    check = PlayerGerName(player); 
    if (strcmp(name, check) == 0)
    {
        printf("player test 1 pass \n");
    }
    else
    {
        printf("player test 1 fail \n");
    }
    PlayerHandCreate(player);
    test  = PlayerSort(player);
    if (test == ERR_OK)
    {
        printf("player test 2 pass \n");
    }
    else
    {
        printf("player test 2 fail \n");
    }
    test = PlayerGetScore(player);
    if (test == 0)
    {
        printf("player test 3 pass \n");
    }
    else
    {
        printf("player test 3 fail \n");
    }
    
    
}

void testDeckCreate()
{
    int deal;
    int *check;
    check = DeckCreate();
    if (check[0] == 1)
    {
        printf("deck test 1 pass \n");
    }
    else
    {
        printf("deck test 1 fail \n");
    }
    deal = DeckDeal(check);
    if (deal > -1 && deal < 52)
    {
         printf("deck test 2 pass \n");
    }
    else
    {
        printf("deck test 2 fail \n");
    }
    deal = DeckDeal(NULL);
    if (deal == 0)
    {
        printf("deck test 3 pass \n");
    }
    else
    {
        printf("deck test 3 fail \n");
    }
    deal = DeckDestroy(check); 
    if (deal == ERR_OK)
    {
        printf("deck test 4 pass \n");
    }    
    else
    {
        printf("deck test 4 fail \n");

    }
}
/* void testHand()
{
    Hand *hand;
    hand = handCreate
}
 */

