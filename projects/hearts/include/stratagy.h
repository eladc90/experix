#ifndef __STRATAGY_H__
#define __STRATAGY_H__
#include "Deck.h"
#include "hand.h"
#include "table.h"


int Strategy(Hand *_hand, Table *_table, int *_cardIndex, int _playerIndex, int _strategy);

char *PrintOption(Hand *_hand);










#endif /*__STRATAGY_H__*/