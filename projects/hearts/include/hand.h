#ifndef __HAND_H__
#define __HAND_H__

#include "vector.h"
#include "heap.h"
#include "player.h"

typedef struct Hand Hand;


/* this function create an hand 

input:
	none
output:
	a pointer to the hand
error:
	if allocation fail return NULL
*/
Hand *handCreate();

/* this function destroy an hand

input:
	a pointer to the hand
output:
	none
error:
*/

void HandDestroy(Hand *_hand);

/* this function add a card to the hand

input:
	a pointer to the player hand and a pointer to a deck of cards

output:
	return status
error:
*/

ADTErr HandAddCard(Hand *_playerHand, int *_cardArr);


/* this function sort the card in the hand by they suit and rank

input:
	a pointer to the hand 

output:
	status

error:
*/

ADTErr HandSort(Hand *_hand);


/* this function check if there is quenn club card in the hand

input:
	a pointer to the hand
output:
	return 0 if not and index number if yes
error:
*/

int HandCheck(Hand *_hand);

/* this function print the hand */

char *PrintHand(Hand *_hand);

/* this function remove a card from the hand 

input:
	a pointer to the hand a cerd and an index number
output:
	none
*/

void HandRemoveCard(Hand *_hand, int _card, int index);




/* this function return the number of card in a specific suit

input:
	a pointer to the hand and a index of suit
output:
	return the number of cards in the suit 
*/


int HandSuitSize(Hand *_hand, int _suit);

/* this function get a card from the hand by suit (_vecIndex) and by index (_cardIndex)

input:
	a pointer to the hand and two index number
output:
	return the card in the index place
error:
*/

int HandGetCard(Hand *_hand, int _vecIndex, int _cardIndex);

/* 
this function set the size of every suit in the hand

input:
	a pointer to the hand
output:
	none
*/

void HandSuitInit(Hand *_hand);

/* this function return the number of card of a specific suit

in the hand 

input:
	a pointer to the hand and index number for the suit

output:
	return the number of card in the suit
*/

int HandVecSize(Hand *_hand, int _ind);

/*this function return the original size of the suit

input:
	a pointer to the hand and a suit
output:
	return the original size of the suit
*/
int HandOrigiSize(Hand *_hand, int _suit);





#endif /*__HAND_H__*/
