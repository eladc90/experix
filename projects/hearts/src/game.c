
#include <stdlib.h> /* malloc */
#include <stdio.h>

#include "game.h"
#include "table.h"
#include "round.h"
#include "player.h"
#include "ADTErr.h"
#include "queue.h"
#include <string.h>

#define MAX_NAME 50
#define NUMBER_OF_PLAYERS 4



static void GameSort(Player **m_playerArr);

struct Game
{
	Player **m_playerArr;
	Table *m_table;
};

Game *GameCreate()
{
	char name[MAX_NAME];
	char autoName[MAX_NAME];
	int index = 0;
	Player **playerArr;
	Table *table;
	Game *game;
	playerArr = (Player **) malloc (sizeof (Player *) * NUMBER_OF_PLAYERS);
	if (playerArr == NULL)
	{
		return NULL;
	}
	table = TableCreate();
	if (table == NULL)
	{
		free(playerArr);
		return NULL;
	}
	game = (Game *) malloc (sizeof (Game));

	printf("enter player name: \n");
	scanf("%s", name);
	playerArr[index] = PlayerCreate(name, 1);
	for (index = 1; index < NUMBER_OF_PLAYERS; index++)
	{
		strncpy(autoName,"player ", 8);
		autoName[9] = index + '0';
		playerArr[index] = PlayerCreate(autoName, 0);
	}
	game -> m_playerArr = playerArr;
	game -> m_table = table;
	return game;
}


ADTErr GamePlay(Game *_game)
{
	int index = 1;
	if (_game == NULL)
	{
		return ERR_NULL;
	}
	while(index > 0)
	{
		roundCreate(_game -> m_playerArr,_game -> m_table);
		GameSort(_game -> m_playerArr);
		index = RoundPlay(_game -> m_playerArr, _game -> m_table);
		roundDestroy(_game -> m_playerArr);
		
	} 
	return ERR_OK;
}


ADTErr GameDestroy(Game *_game)
{
	int index = 0;
	for (; index < NUMBER_OF_PLAYERS; index++)
	{
		free(_game -> m_playerArr[index]);
	}
	free(_game -> m_playerArr);
	free(_game -> m_table);
	return ERR_OK;
}

/*============================================== statics functions ===================================*/


static void GameSort(Player **m_playerArr)
{
	int index = 0;
	if(m_playerArr == NULL)
	{
		return;
	}
	for (; index < NUMBER_OF_PLAYERS; index++)
	{
		PlayerSort(m_playerArr[index]);
	}
	
}
