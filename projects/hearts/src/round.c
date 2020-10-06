
#include "trick.h"
#include "player.h"
#include "hand.h"
#include <stdio.h>
#define MAX_NUMBER_OF_ROUNDS 13
#define NUMBER_OF_PLAYERS 4



static ADTErr RoundDeal(Player *_player, int *_cards);


ADTErr roundCreate(Player **_playerArr, Table *_table)
{
    int index = 0;
    int *deck;
    deck = DeckCreate();
    for (; index < NUMBER_OF_PLAYERS; index++)
    {
        PlayerHandCreate(_playerArr[index]);
        RoundDeal(_playerArr[index], deck);
        PlayerSuitSize(_playerArr[index]);
    }
    DeckDestroy(deck); 
	return 0;
}

ADTErr roundDestroy(Player **_playerArr)
{
    int index = 0;
    for (; index < NUMBER_OF_PLAYERS; index++)
    {
        PlayerDestroyHand(_playerArr[index]);
    }
    return ERR_OK;
}


int RoundPlay(Player **_playerArr, Table *_table)
{
    int isOver = 1;
    isOver = TrickPlay(_playerArr, _table);
    if (isOver == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*============================================== statics functions ===================================*/

static ADTErr RoundDeal(Player *_player, int *_cards)
{
    if (_player == NULL || _cards == NULL)
    {
        return ERR_NULL;
    }
    PlayerAdd(_player, _cards);
    return ERR_OK;
}
