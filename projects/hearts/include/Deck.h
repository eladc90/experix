#ifndef __DECK_H__
#define __DECK_H__
#include "ADTErr.h"


typedef enum   
{ 
    SPADES,
    HEARTS,
    DIAMONDS,
    CLUBS 
}Suits;

typedef enum   
{
    DEUCE,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE 
}Rank;




/* this function create a deck of cards

input:
    none
output:
    return a pointer to the created decks
error:
*/
int *DeckCreate();

int DeckDeal(int *_cardArr);

ADTErr DeckDestroy(int *_deck);


#endif /*__DECK_H__*/
