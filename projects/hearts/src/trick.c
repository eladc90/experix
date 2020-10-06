#include "game.h"
#include "trick.h"
#include "round.h"
#include "table.h"
#include "player.h"
#include "ui.h"
#include <stdio.h>
#include <string.h> /*create string */
#define NUMBER_OF_ROUNDS 13
#define NUMBER_OF_PLAYERS 4
#define PLAYER_LOSE -1
#define MAX_SIZE_OF_CHAR 1000
#define MAX_NAME 50


int trickGetScore(Table *_table);

int trickGetNextPlayer(Table *_table);

void trickGetCards(Player **_playerArr, Table *_table, int _firstPlayer);

int TrickGetFirstPlayer(Player **_playerArr);


int TrickPlay(Player **_playerArr, Table *_table)
{
    int i = 0;
    int firstPlayer;
    int score;
    int totalScore;
    firstPlayer  = TrickGetFirstPlayer(_playerArr);

    while(i < NUMBER_OF_ROUNDS)
    {
        trickGetCards(_playerArr, _table, firstPlayer);
        TablePlay(_table, firstPlayer);
        firstPlayer = trickGetNextPlayer(_table);
        score = trickGetScore(_table);
        totalScore = PlayerAddScore(_playerArr[firstPlayer], score);
        if (totalScore == 0)
        {
            return 1;
        }

        TableZeroScore(_table);
        TableZero(_table);
        UiPrintScore(_playerArr);
        i++;
    }
    return 0;
}

char *TrickPrintScore(Player **_playerArr)
{
    int index = 0;
    char *score;
    char charTemp[MAX_NAME];
    int temp;
    score = (char *) malloc (sizeof(char) * MAX_SIZE_OF_CHAR);
    for (; index < NUMBER_OF_PLAYERS; index++)
    {
        strcpy(charTemp, PlayerGerName(_playerArr[index]));
        strncat(score, charTemp, MAX_NAME);
        strncat(score, ":  ", 10);
        temp = PlayerGetScore(_playerArr[index]);
        sprintf(charTemp, "%d", temp);
        strncat(score, charTemp, 10);
        strncat(score, "   ", 10);
    }
    return score;
}

void trickGetCards(Player **_playerArr, Table *_table, int _firstPlayer)
{
    int index = _firstPlayer;
    int tableIndex = 0;
    int playerIndex = 1;

    PlayerPlay(_playerArr[_firstPlayer], _table, 1, tableIndex, 0);
    for (index = (_firstPlayer + 1) % NUMBER_OF_PLAYERS, tableIndex = 1 ;index != _firstPlayer; playerIndex++, index = (index + 1) % NUMBER_OF_PLAYERS, tableIndex++)
    {
        PlayerPlay(_playerArr[index], _table, 1, tableIndex, playerIndex);
    }
}



int TrickGetFirstPlayer(Player **_playerArr)
{
    int startPla = 0;
    int index = 0;
    for (; index < NUMBER_OF_PLAYERS; index ++)
    {
        startPla =  PlayerCheckFirst(_playerArr[index]);
        if (startPla != 0)
        {
            return index;
        }
    }
    return 0;
}

int trickGetNextPlayer(Table *_table)
{
    return TableGetLoser(_table);
}

int trickGetScore(Table *_table)
{
    return TableAddScore(_table);
}
