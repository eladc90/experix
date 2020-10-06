#include <stdlib.h>
#include <stdio.h> 
#include <string.h> /* create a string */

#include "hand.h"
#include "Deck.h"
#include "ADTErr.h"
#include "vector.h"
#include "heap.h"
#include "player.h"

#define NUMBER_OF_PLAYERS 4
#define CARDS_IN_SUIT 13
#define HAND_NUMBER_OF_CARDS 13
#define NUMBER_OF_SUIT 4
#define MAX_SIZE_OF_CHAR 500

#define RANK(num)\
        (num)%(CARDS_IN_SUIT)
        
#define SUIT(num)\
        (num)/(CARDS_IN_SUIT)



void HandSuitInit(Hand *_hand);

int HandCheck(Hand *_hand);

ADTErr HandSort(Hand *_hand);

struct Hand
{
    	Heap **m_cards;
		int m_handSize;
		Vector **m_vector;

		int m_spades;
		int m_hearts;
		int m_dimonds;
		int m_clubs;

		int m_originalSpades;
		int m_originalHearts;
		int m_originalDimonds;
		int m_originalClubs;
};

Hand *handCreate()
{
	int index;
	Hand *hand;
	Heap **heap;
	Vector **vec;
	hand = (Hand *) malloc (sizeof(Hand) * NUMBER_OF_SUIT);
	if (hand == NULL)
	{
		return NULL;
	}
	heap = (Heap **) malloc (sizeof(Heap *)* NUMBER_OF_SUIT);
	if (heap == NULL)
	{
		return NULL;
	}
	vec = (Vector **) malloc (sizeof(Vector *) * NUMBER_OF_SUIT);
	if (vec == NULL)
	{
		return NULL;
	}
	hand -> m_vector = vec;
	hand -> m_cards = heap;
	for (index = 0; index < NUMBER_OF_SUIT; index++)
	{
		(hand -> m_vector[index]) = VectorCreate(HAND_NUMBER_OF_CARDS, 1);
		(hand -> m_cards[index]) = HeapBuild(*(hand -> m_vector + index));
		if (*(hand -> m_vector + index) == NULL)
		{
			free(hand -> m_vector + index);
			free(hand -> m_cards + index);
		}
	}
	return hand;
}

void HandSuitInit(Hand *_hand)
{
	VectorItemsNum(_hand -> m_vector[0], &_hand -> m_spades);
	VectorItemsNum(_hand -> m_vector[1], &_hand -> m_hearts);
	VectorItemsNum(_hand -> m_vector[2], &_hand -> m_dimonds);
	VectorItemsNum(_hand -> m_vector[3], &_hand -> m_clubs);
	VectorItemsNum(_hand -> m_vector[0], &_hand -> m_originalSpades);
	VectorItemsNum(_hand -> m_vector[1], &_hand -> m_originalHearts);
	VectorItemsNum(_hand -> m_vector[2], &_hand -> m_originalDimonds);
	VectorItemsNum(_hand -> m_vector[3], &_hand -> m_originalClubs);	
}

int HandVecSize(Hand *_hand, int _ind)
{
	int size;
	if (_ind == 0)
	{
		VectorItemsNum(_hand -> m_vector[0], &size);
	}
	if (_ind == 1)
	{
		VectorItemsNum(_hand -> m_vector[1], &size);
	}
	if (_ind == 2)
	{
		VectorItemsNum(_hand -> m_vector[2], &size);
	}
	if (_ind == 3)
	{
		VectorItemsNum(_hand -> m_vector[3], &size);
	}
	return size;
}





void HandDestroy(Hand *_hand)
{
	int index = 0;
	for (; index < NUMBER_OF_SUIT; index++)
	{
		VectorDestroy(_hand -> m_vector[index]);
		HeapDestroy(_hand -> m_cards[index]);
	}
	free(_hand -> m_cards);
	free(_hand -> m_vector);
	free(_hand);
}


ADTErr HandSort(Hand *_hand)
{
	int index = 0;
	if (_hand == NULL)
	{
		return ERR_NULL;
	}
	for (; index < NUMBER_OF_SUIT; index++)
	{
		_hand -> m_cards[index] = HeapBuild(*(_hand -> m_vector + index));
	}
	return ERR_OK;
}


int HandCheck(Hand *_hand)
{
	int temp = 0;
	int index = 0;
	int checkIndex = 0;
	for (; index < NUMBER_OF_PLAYERS; index++)
	{
		for (;checkIndex < HAND_NUMBER_OF_CARDS; checkIndex++)
		{
			VectorGet(_hand -> m_vector[index], checkIndex, &temp);
			if (temp == 40)
			{
				return index;
			}
		}
	}
	return 0;
}


ADTErr HandAddCard(Hand *_playerHand, int *_cardArr)
{
	int card;
	card = DeckDeal(_cardArr);
	VectorAdd(_playerHand -> m_vector[SUIT(card)], card);
	return ERR_OK;
} 


void HandRemoveCard(Hand *_hand, Card _card, int _index)
{
	VectorSet(_hand -> m_vector[SUIT(_card)], _index, -1);
	if (SUIT(_card) == 0)
	{
		_hand -> m_spades--;
	}
	if (SUIT(_card) == 1)
	{
		_hand -> m_hearts--;
	}
	if (SUIT(_card) == 2)
	{
		_hand -> m_dimonds--;
	}
	if (SUIT(_card) == 3)
	{
		_hand -> m_clubs--;
	}
}

char *PrintHand(Hand *_hand)
{
	char *hand;
	int index = 0;
	int indexOfCard = 0;
	int card;
	int sizeOfVec = 0;
	char temp[10];
	hand = (char *) malloc (sizeof(char) * MAX_SIZE_OF_CHAR);
	if (hand == NULL)
	{
		return NULL;
	}
	hand[0] = '\0';
	for (; index < NUMBER_OF_PLAYERS; index++)
	{
		VectorItemsNum(_hand -> m_vector[index], &sizeOfVec);
		for (indexOfCard = 0; indexOfCard < sizeOfVec; indexOfCard++)
		{
			
			VectorGet(_hand -> m_vector[index], indexOfCard, &card);
			if (card == -1)
			{
				continue;
			}
			if ((RANK(card)) >= 10)
			{
				temp[0] = '1';
				strncat(hand, temp, 1);
				temp[0] = ((RANK(card)%10) + '0');
				strncat(hand, temp, 1);
			}
			else
			{
				temp[0] = (RANK(card) + '0');
				strncat(hand, temp, 2);
			}
			if (SUIT(card) == 0)
			{
				strncat(hand, "S", 2);
			}
			if (SUIT(card) == 1)
			{
				strncat(hand, "H", 2);
			}
			if (SUIT(card) == 2)
			{
				strncat(hand, "D", 2);
			}
			if (SUIT(card) == 3)
			{
				strncat(hand, "C", 2);
			}
			strncat(hand, " ", 2);
		}
	}
	return hand;
}



int HandGetCard(Hand *_hand, int _vecIndex, int _cardIndex)
{
	int card;
	VectorGet(_hand -> m_vector[_vecIndex], _cardIndex, &card);
	return card;
}

int HandSuitSize(Hand *_hand, int _suit)
{
	if (_suit == 0)
	{
		return _hand -> m_spades;
	}
	if (_suit == 1)
	{
		return _hand -> m_hearts;
	}
	if (_suit == 2)
	{
		return _hand -> m_dimonds;
	}
	if (_suit == 3)
	{
		return _hand -> m_clubs;
	}
	return 0;
}

int HandOrigiSize(Hand *_hand, int _suit)
{
	if (_suit == 0)
	{
		return _hand -> m_originalSpades;
	}
	if (_suit == 1)
	{
		return _hand -> m_originalHearts;
	}
	if (_suit == 2)
	{
		return _hand -> m_originalDimonds;
	}
	if (_suit == 3)
	{
		return _hand -> m_originalClubs;
	}
	return 0;
}





