#define MAX_NAME 50
#define MAGIC_NUMBER 851981652
#define NUMBER_OF_PLAYERS 4
#define NUMBER_OF_CARDS 13
#include <string.h>
#include "player.h"
#include "hand.h"
#include "Deck.h"
#include "stratagy.h"
#include "ADTErr.h"
#include <stdio.h>






void PrintPlayerHand(Player *_player);

int PlayerCheckFirst(Player *_player);

ADTErr PlayerSort(Player *_player);

struct Player
{
    char m_name[MAX_NAME];
    int m_score;
    Hand *m_hand;
    int m_human;
    int m_magicNumber;
};


Player *PlayerCreate(char *_name, int _isHuman)
{
    Player *player;
    player = (Player *) malloc (sizeof (Player));
    if (player == NULL)
    {
        return NULL;
    }
    player -> m_magicNumber = MAGIC_NUMBER;
    player -> m_score = 0;
    player -> m_human = _isHuman;
    if (_name == NULL)
    {
        strncpy(player -> m_name , "player", strlen("player"));	
        return player;
    }
    strncpy(player -> m_name , _name, strlen(_name));
    PlayerHandCreate(player);
    return player;
}


void PlayerHandCreate(Player *_player)
{
    _player -> m_hand = handCreate();
}

void PlayerSuitSize(Player *_player)
{
    HandSuitInit(_player -> m_hand);
}

void PlayerDestroyHand(Player *_player)
{
    HandDestroy(_player -> m_hand);
}

ADTErr PlayerSort(Player *_player)
{
    HandSort(_player -> m_hand);
    return ERR_OK;
}


int PlayerCheckFirst(Player *_player)
{
    int firstPlayer = 0;
    firstPlayer = HandCheck(_player -> m_hand);
    return firstPlayer;
}



int PlayerPlay(Player *_player, Table *_table,  int _strategy, int _index, int _playerIndex)
{
    int cardIndex;
    int card;
    card = Strategy(_player -> m_hand, _table, &cardIndex, _playerIndex, _player -> m_human);
    TableAddCard(_table , card, _index);
    HandRemoveCard(_player -> m_hand, card, cardIndex);
    return card;
}

int PlayerGetScore(const Player *_player)
{
    if (_player == NULL)
    {
        return 0;
    }
    return _player -> m_score;
}

ADTErr PlayerAdd(Player *_player, int *Card)
{
    int index = 0;
    if (_player == NULL)
    {
        return ERR_NULL;
    }
    for (; index < NUMBER_OF_CARDS; index++)
    {
        HandAddCard(_player -> m_hand, Card);
    }
    return ERR_OK;
}


char *PlayerGerName(Player *_player)
{
    return _player -> m_name;
}

int PlayerAddScore(Player *_player, int _score)
{
    _player -> m_score = _player -> m_score + _score;
    if (_player -> m_score >= 100)
    {
        return 0;
    }
    return 1;
}


void PrintPlayerHand(Player *_player)
{
    PrintHand(_player -> m_hand);
}







