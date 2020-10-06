#include <stdlib.h> /* size_t */
#include <stdio.h>
#include <string.h>
#include "Deck.h"
#include "table.h"
#include "queue.h"
#include "ADTErr.h"
#include "ui.h"
#define SIZE_OF_TABLE 4
#define NUM_OF_PLAYERS 4
#define CARDS_IN_SUIT 13
#define QUEEN_SPADES 49
#define QUEEN_SPADES_PEN 13
#define HEARTS_PEN 1
#define MAX_SIZE_OF_CHAR 500

#define RANK(num)\
        (num)%(CARDS_IN_SUIT)
        
#define SUIT(num)\
        (num)/(CARDS_IN_SUIT)



static int TableGetScore(int _card);

struct Table
{
	int *m_table;
	int m_loser;
	int m_loserIndex;
	int m_tableScore;
};


Table *TableCreate()
{
	int index = 0;
	int *arr;
	Table *table;
	table = (Table *) malloc (sizeof(Table));
	if (table == NULL)
	{
		return NULL;
	}
	arr = (int *) malloc (sizeof(int) * SIZE_OF_TABLE);
	if (arr == NULL)
	{
		free(table);
		return NULL; 
	}
	for (;index < NUM_OF_PLAYERS; index++)
	{
		arr[index] = -1;
	}
	table -> m_table = arr;
	
	return table;
}


ADTErr TableAddCard(Table *_table, Card _card, int index)
{
	_table -> m_table[index] =  _card;
	return ERR_OK;
}


ADTErr TablePlay(Table *_table, int _firstPlayer)
{
	int TempCard = 0;
	int index = 0;
	if (_table == NULL)
	{
		return ERR_NULL;
	}
	while (index < SIZE_OF_TABLE)
	{
		TempCard = _table -> m_table[index];
		_table -> m_tableScore += TableGetScore(TempCard);
		if (TempCard > 	_table -> m_loser)
		{
			_table -> m_loser = TempCard;
			_table -> m_loserIndex = (index + _firstPlayer) % NUM_OF_PLAYERS;
		}
		index++;
	}
	UiPrintTable(_table);
	printf("\n"); 
	printf("this is the loser : %d\n", TableGetLoser(_table)); 
	return ERR_OK;
}


int TableGetLoser(Table *_table)
{
	return _table -> m_loserIndex;
}

int TableAddScore(Table *_table)
{
	return _table -> m_tableScore;
}

void TableZeroScore(Table *_table)
{
	_table -> m_tableScore = 0;
	_table -> m_loser = -1;
	_table -> m_loserIndex = -1;
	return;
}

void TableZero(Table *_table)
{
	int index = 0;
	for (; index < NUM_OF_PLAYERS; index++)
	{
		_table -> m_table[index] = -1;
	}
}

int TableGetCard(Table *_table, int _index)
{
	return _table -> m_table[_index];
}

char *PrintTable(Table *_table)
{
	char *table;
	int index = 0;
	int card;
	char temp[10];
	table = (char *) malloc (sizeof(char) * MAX_SIZE_OF_CHAR);
	table[0] = '\0';
	for (; index < SIZE_OF_TABLE; index++)
	{
		card = _table -> m_table[index];
		if (card == -1)
		{
			continue;
		}
		if ((RANK(card)) >= 10)
		{
			temp[0] = '1';
			strncat(table, temp, 1);
			temp[0] = ((RANK(card)%10) + '0');
			strncat(table, temp, 1);
		}
		else
		{
			temp[0] = (RANK(card) + '0');
			strncat(table, temp, 2);
		}
		if (SUIT(card) == 0)
		{
			strncat(table, "S", 2);
		}
		if (SUIT(card) == 1)
		{
			strncat(table, "H", 2);
		}
		if (SUIT(card) == 2)
		{
			strncat(table, "D", 2);
		}
		if (SUIT(card) == 3)
		{
			strncat(table, "C", 2);
		}
		strncat(table, " ", 2);
	}
	return table;
}



/*============================================== statics functions ===================================*/

static int TableGetScore(Card _card)
{
	if (SUIT(_card) == 1)
	{
		
		return HEARTS_PEN;
	}
	if (_card == QUEEN_SPADES)
	{
		return QUEEN_SPADES_PEN;
	}
	return 0;
}







