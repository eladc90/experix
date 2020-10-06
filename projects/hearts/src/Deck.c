#include <stdlib.h>  /*malloc + size_t*/
#include "Deck.h"
#include "ADTErr.h"
#include "player.h"

#define MAGIC_NUM 549156115
#define DECK_SIZE 52

static int *CreateCards(int *_cardArr);


int *DeckCreate()
{
    int *cardArr;
    cardArr = (int*) malloc (sizeof(int) * DECK_SIZE);
    if (cardArr == NULL)
    {
        return NULL;
    }
    cardArr = CreateCards(cardArr);
    return cardArr;
} 

static int *CreateCards(int *_cardArr)
{
    int index;
    for (index = 0; index < DECK_SIZE; index++)
    {
        _cardArr[index] = 1;
    }
    return _cardArr;
}



int DeckDeal(int *_cardArr)
{
    int index = -1;
	if (_cardArr == NULL)
	{
		return 0;
	}
	while (1)
	{
		index = rand()%DECK_SIZE;
		if (_cardArr[index] == 1)
		{
		    _cardArr[index] = 0;
		    return index;
		}
	}
	return index;
}


ADTErr DeckDestroy(int *_deck)
{
    if (_deck == NULL)
    {
        return ERR_NULL;
    }
    free(_deck);
    return ERR_OK;
}



